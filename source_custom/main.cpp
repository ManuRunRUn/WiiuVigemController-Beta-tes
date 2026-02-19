#include "console.h"
#include "vpad_to_json.h"
#include "udp.h"
#include <whb/proc.h>
#include <coreinit/screen.h>
#include <padscore/kpad.h>
#include <vpad/input.h>
#include <arpa/inet.h>
#include <nn/ac.h>
#include <whb/sdcard.h>
#include <coreinit/cache.h>
#include <proc_ui/procui.h>
#include <sysapp/launch.h>
#include <wut_types.h>
#include <ini.h>
#include <cstring>
#include <sys/unistd.h>
#include <thread>
#include <format>

/**
 * Application configuration.
 */
typedef struct {
    std::string ipaddress;
    uint16_t port{4242};
} configuration;

/**
 * Whether pad data are being sent.
 */
static std::atomic<bool> thread_running{true};

/**
 * Screen state for power saving.
 */
static std::atomic<bool> screen_enabled{true};

/**
 * Handler for ini parser.
 * @param user User data.
 * @param section Section name.
 * @param name Name.
 * @param value Value.
 * @return Returns nonzero on success, zero on error.
 */
static int handler(void* user, const char* section, const char* name, const char* value)
{
    configuration* pconfig = static_cast<configuration*>(user);
    if(std::strcmp(section, "server") == 0) {
        if(std::strcmp(name, "ipaddress") == 0) {
            pconfig->ipaddress = value;
        }
        else if(std::strcmp(name, "port") == 0) {
            pconfig->port = std::atoi(value);
        }
        else {
            return 0; // Unknown name
        }
    }
    else {
        return 0; // Unknown section
    }
    return 1;
}

/**
 * Print the custom header.
 */
static void PrintHeader(OSScreenID bufferNum)
{
    OSScreenPutFontEx(bufferNum, 0, 0, " __      _____ _  _   _   _  __   ___  ___       ___          ");
    OSScreenPutFontEx(bufferNum, 0, 1, " \\ \\    / /_ _(_)| | | | | | \\ \\ / (_)/ __|___ _|   \\ _  _ ___");
    OSScreenPutFontEx(bufferNum, 0, 2, "  \\ \\/\\/ / | || || |_| | | |  \\ V / | | (_ / -_)| |) | || (_-<");
    OSScreenPutFontEx(bufferNum, 0, 3, "   \\_/\\_/ |___|_| \\___/  |_|   \\_/  |_|\\___|___|___/ \\_,_/__/");
    OSScreenPutFontEx(bufferNum, 0, 4, "                                                    v1.0.0");
}

/**
 * Print credits.
 */
static void PrintCredits(OSScreenID bufferNum, int startLine)
{
    OSScreenPutFontEx(bufferNum, 0, startLine, "Based on MiisendU by Crayon");
    OSScreenPutFontEx(bufferNum, 0, startLine + 1, "GitHub: https://github.com/Crayon2000/MiisendU-Wii-U");
    OSScreenPutFontEx(bufferNum, 0, startLine + 2, "Wiki: https://wiiubrew.org/wiki/UsendMii");
}

/**
 * Reset orientation.
 */
static void ResetOrientation()
{
    // Posture with the gamepad up and straight in front of user
    static VPADDirection dir_base = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    VPADSetGyroAngle(VPAD_CHAN_0, 0.0f, 0.0f, 0.0f);
    VPADSetGyroDirection(VPAD_CHAN_0, &dir_base);
    VPADSetGyroDirReviseBase(VPAD_CHAN_0, &dir_base);
}

/**
 * Send pad data to UDP.
 * @return Returns 0 when done.
 */
static int sendPadData() {
    while(thread_running == true) {
        // Gamepad key state data
        VPADReadError error;
        VPADStatus vpad_data;

        KPADError kpad_error1 = KPADError::KPAD_ERROR_UNINITIALIZED;
        KPADError kpad_error2 = KPADError::KPAD_ERROR_UNINITIALIZED;
        KPADError kpad_error3 = KPADError::KPAD_ERROR_UNINITIALIZED;
        KPADError kpad_error4 = KPADError::KPAD_ERROR_UNINITIALIZED;
        KPADStatus kpad_data1;
        KPADStatus kpad_data2;
        KPADStatus kpad_data3;
        KPADStatus kpad_data4;
        HPADStatus hpad_data1[16];
        HPADStatus hpad_data2[16];
        HPADStatus hpad_data3[16];
        HPADStatus hpad_data4[16];

        // Read the VPAD
        VPADRead(VPAD_CHAN_0, &vpad_data, 1, &error);

        // Read the KPADs
        KPADReadEx(WPAD_CHAN_0, &kpad_data1, 1, &kpad_error1);
        KPADReadEx(WPAD_CHAN_1, &kpad_data2, 1, &kpad_error2);
        KPADReadEx(WPAD_CHAN_2, &kpad_data3, 1, &kpad_error3);
        KPADReadEx(WPAD_CHAN_3, &kpad_data4, 1, &kpad_error4);

        // Flush the cache (may be needed due to continuous refresh of the data ?)
        DCFlushRange(&vpad_data, sizeof(VPADStatus));

        // Transform to JSON
        PADData pad_data;
        std::memset(&pad_data, 0, sizeof(PADData));
        pad_data.vpad = &vpad_data;
        if(kpad_error1 == KPADError::KPAD_ERROR_OK) {
            pad_data.kpad[0] = &kpad_data1;
        }
        if(kpad_error2 == KPADError::KPAD_ERROR_OK) {
            pad_data.kpad[1] = &kpad_data2;
        }
        if(kpad_error3 == KPADError::KPAD_ERROR_OK) {
            pad_data.kpad[2] = &kpad_data3;
        }
        if(kpad_error4 == KPADError::KPAD_ERROR_OK) {
            pad_data.kpad[3] = &kpad_data4;
        }
        if(HPADRead(HPAD_CHAN_0, &hpad_data1[0], 16) >= 0) {
            for(uint8_t i = 0; i < 16; ++i) {
                if(hpad_data1[i].error == 0) {
                    pad_data.hpad[0] = &hpad_data1[i];
                    break;
                }
            }
        }
        if(HPADRead(HPAD_CHAN_1, &hpad_data2[0], 16) >= 0) {
            for(uint8_t i = 0; i < 16; ++i) {
                if(hpad_data2[i].error == 0) {
                    pad_data.hpad[1] = &hpad_data2[i];
                    break;
                }
            }
        }
        if(HPADRead(HPAD_CHAN_2, &hpad_data3[0], 16) >= 0) {
            for(uint8_t i = 0; i < 16; ++i) {
                if(hpad_data3[i].error == 0) {
                    pad_data.hpad[2] = &hpad_data3[i];
                    break;
                }
            }
        }
        if(HPADRead(HPAD_CHAN_3, &hpad_data4[0], 16) >= 0) {
            for(uint8_t i = 0; i < 16; ++i) {
                if(hpad_data4[i].error == 0) {
                    pad_data.hpad[3] = &hpad_data4[i];
                    break;
                }
            }
        }

        // Convert the data to JSON and send it
        std::string_view msg = pad_to_json(pad_data);
        udp_print(msg);

        // Make a small delay to prevent filling up the computer receive buffer
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

/**
 * Entry point.
 * @param argc An integer that contains the count of arguments.
 * @param argv An array of null-terminated strings representing command-line arguments.
 * @return Returns zero on success, nonzero on error.
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    uint8_t IP[4] = {192, 168, 1, 100};

    WHBProcInit();
    VPADInit();
    KPADInit();
    HPADInit();
    WPADEnableURCC(true);

    WHBMountSdCard();
    char *sdRootPath = WHBGetSdCardMountPath();
    const std::string path = std::format("{}/wiiu/apps/WiiUViGEmBusController/settings.ini", sdRootPath);

    // Init screen and screen buffers
    ConsoleInit();

    // Clear screens
    ConsoleDrawStart();

    // Gamepad key state data
    VPADReadError error;
    VPADStatus vpad_data;

    int8_t selected_octet = 0;

    // Read default settings from file
    bool ip_loaded = false;
    configuration config;
    ini_parse(path.c_str(), handler, &config);
    const uint16_t Port = config.port;
    if(config.ipaddress.empty() == false && inet_pton(AF_INET, config.ipaddress.c_str(), &IP) > 0) {
        ip_loaded = true;
    }
    if (ip_loaded == false && nn::ac::Initialize() == true) {
        if (uint32_t ac_ip = 0; nn::ac::GetAssignedAddress(&ac_ip) == true) {
            IP[0] = (ac_ip >> 24) & 0xFF;
            IP[1] = (ac_ip >> 16) & 0xFF;
            IP[2] = (ac_ip >>  8) & 0xFF;
            IP[3] = (ac_ip >>  0) & 0xFF;
        }
        nn::ac::Finalize();
    }

    bool running = true;

    uint32_t wait_time_horizontal = 0;
    uint32_t wait_time_vertical = 0;
    const uint8_t wait_time = 8; // Reduced for faster input

    // IP address input with improved speed
    while(running == true) {
        VPADRead(VPAD_CHAN_0, &vpad_data, 1, &error);
        
        // Faster navigation with L/R buttons for octet selection
        if (vpad_data.trigger & VPAD_BUTTON_L && selected_octet > 0) {
            selected_octet--;
        }
        if (vpad_data.trigger & VPAD_BUTTON_R && selected_octet < 3) {
            selected_octet++;
        }
        
        // Fast increment/decrement with +10 using ZL/ZR
        if (vpad_data.trigger & VPAD_BUTTON_ZL) {
            IP[selected_octet] = (IP[selected_octet] >= 10) ? (IP[selected_octet] - 10) : 0;
        }
        if (vpad_data.trigger & VPAD_BUTTON_ZR) {
            IP[selected_octet] = (IP[selected_octet] <= 245) ? (IP[selected_octet] + 10) : 255;
        }
        
        // Standard up/down for single digit
        if (vpad_data.hold & VPAD_BUTTON_UP) {
            if (vpad_data.trigger & VPAD_BUTTON_UP || wait_time_vertical++ > wait_time) {
                IP[selected_octet] = (IP[selected_octet] < 255) ? (IP[selected_octet] + 1) : 0;
                wait_time_vertical = 0;
            }
        }
        if (vpad_data.hold & VPAD_BUTTON_DOWN) {
            if (vpad_data.trigger & VPAD_BUTTON_DOWN || wait_time_vertical++ > wait_time) {
                IP[selected_octet] = (IP[selected_octet] > 0) ? (IP[selected_octet] - 1) : 255;
                wait_time_vertical = 0;
            }
        }

        if(ConsoleDrawStart() == true) {
            PrintHeader(SCREEN_DRC);
            OSScreenPutFontEx(SCREEN_DRC, 0, 6, "Enter your PC IP address:");
            OSScreenPutFontEx(SCREEN_DRC, 0, 7, "L/R: Switch octet | ZL/ZR: +/-10 | UP/DOWN: +/-1");
            OSScreenPutFontEx(SCREEN_DRC, selected_octet * 4, 9, "vvv");
            OSScreenPutFontEx(SCREEN_DRC, 0, 10, std::format("{:3}.{:3}.{:3}.{:3}", IP[0], IP[1], IP[2], IP[3]).c_str());
            OSScreenPutFontEx(SCREEN_DRC, 0, 13, "Press 'A' to connect");
            OSScreenPutFontEx(SCREEN_DRC, 0, 14, "Hold HOME to exit");
            PrintCredits(SCREEN_DRC, 16);

            ConsoleDrawEnd();
        }

        if (vpad_data.trigger & VPAD_BUTTON_A) {
            break;
        }

        running = WHBProcIsRunning();
    }
    if(running == false) {
        WHBUnmountSdCard();
        ConsoleFree();
        WHBProcShutdown();
        return 0;
    }

    // Disallow TV Menu
    VPADSetTVMenuInvalid(VPAD_CHAN_0, true);

    bool fromHBL;
    if(OSIsHomeButtonMenuEnabled() == false) {
        fromHBL = true;
    }
    else {
        fromHBL = false;

        // Disable HOME button menu
        OSEnableHomeButtonMenu(false);
    }

    // Reset orientation
    ResetOrientation();

    // Get IP Address (without spaces)
    const std::string IP_ADDRESS = std::format("{}.{}.{}.{}", IP[0], IP[1], IP[2], IP[3]);

    // Initialize the UDP connection
    udp_init(IP_ADDRESS, Port);

    // Save settings to file
    FILE * IP_file = std::fopen(path.c_str(), "w");
    if (IP_file != nullptr) {
        std::fprintf(IP_file,
            "[server]\n"
            "ipaddress=%s\n"
            "port=%d\n"
            "\n",
            IP_ADDRESS.c_str(), Port);
        std::fclose(IP_file);
    }

    uint16_t holdTime = 0;
    bool last_touch_state = false;

    // Start to send pad data
    std::thread pad_thread(sendPadData);

    while(running == true) {
        VPADRead(VPAD_CHAN_0, &vpad_data, 1, &error);
        DCFlushRange(&vpad_data, sizeof(VPADStatus));

        // Touch screen to toggle display
        if(vpad_data.tpNormal.touched && !last_touch_state) {
            screen_enabled = !screen_enabled;
            if(!screen_enabled) {
                // Clear DRC screen when turning off (double buffer)
                OSScreenClearBufferEx(SCREEN_DRC, 0x00000000);
                OSScreenFlipBuffersEx(SCREEN_DRC);
                OSScreenClearBufferEx(SCREEN_DRC, 0x00000000);
                OSScreenFlipBuffersEx(SCREEN_DRC);
            }
        }
        last_touch_state = vpad_data.tpNormal.touched;

        if(ConsoleDrawStart() == true) {
            const std::string msg_connected = std::format("Connected to {}:{}", IP_ADDRESS, Port);

            // Print to TV
            PrintHeader(SCREEN_TV);
            OSScreenPutFontEx(SCREEN_TV, 0, 6, msg_connected.c_str());
            OSScreenPutFontEx(SCREEN_TV, 0, 8, "Streaming controller data to PC...");
            if(screen_enabled) {
                OSScreenPutFontEx(SCREEN_TV, 0, 10, "GamePad display: ON (touch to turn off)");
            } else {
                OSScreenPutFontEx(SCREEN_TV, 0, 10, "GamePad display: OFF (touch to turn on)");
            }
            OSScreenPutFontEx(SCREEN_TV, 0, 12, "All controllers are active!");
            OSScreenPutFontEx(SCREEN_TV, 0, 16, "Hold HOME to exit");
            PrintCredits(SCREEN_TV, 13);

            // Print to DRC only if screen is enabled
            if(screen_enabled) {
                PrintHeader(SCREEN_DRC);
                OSScreenPutFontEx(SCREEN_DRC, 0, 6, msg_connected.c_str());
                OSScreenPutFontEx(SCREEN_DRC, 0, 8, "Streaming controller data to PC...");
                OSScreenPutFontEx(SCREEN_DRC, 0, 10, "Touch screen to turn off display");
                OSScreenPutFontEx(SCREEN_DRC, 0, 12, "All controllers active!");
                OSScreenPutFontEx(SCREEN_DRC, 0, 16, "Hold HOME to exit");
                PrintCredits(SCREEN_DRC, 13);
            }

            ConsoleDrawEnd();
        }

        // Check for exit signal
        if (vpad_data.hold & VPAD_BUTTON_HOME && ++holdTime > 400) {
            if(fromHBL == true) {
                running = false;
            }
            else {
                SYSLaunchMenu();
                running = WHBProcIsRunning();
            }
        }
        if (vpad_data.release & VPAD_BUTTON_HOME) {
            holdTime = 0;
        }
    }

    thread_running = false;
    pad_thread.join();

    VPADShutdown();
    KPADShutdown();
    HPADShutdown();
    WHBUnmountSdCard();
    ConsoleFree();
    WHBProcShutdown();

    return 0;
}
