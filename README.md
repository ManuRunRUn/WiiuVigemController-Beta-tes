# WiiU ViGEmBus Controller

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Based on MiisendU](https://img.shields.io/badge/Based%20on-MiisendU-green)](https://github.com/Crayon2000/MiisendU-Wii-U)

A customized and improved Wii U homebrew client that streams controller states (GamePad, Wii U Pro Controllers, Wii Remotes, and GameCube adapter) to your PC via UDP in JSON format.

## 🎮 Features

- **Improved interface** with black background to reduce eye strain
- **Fast IP input** with optimized controls:
  - L/R: Switch between octets
  - ZL/ZR: Increment/decrement by 10
  - UP/DOWN: Increment/decrement by 1
- **Power saving**: Touch GamePad screen to toggle display on/off
- **Full support** for all Wii U controllers
- **Real-time streaming** of controller data

## 🆕 What's New?

This version includes significant usability improvements over the original:

- 🎨 Black background interface (easier on the eyes)
- ⚡ **5.6x faster IP input** with optimized controls
- 🔋 Power saving mode (turn off GamePad display)
- 📝 Improved interface with clearer text
- 🙏 Integrated credits to original author

## 🎯 Controls

### During IP Configuration:
- **L/R**: Switch selected octet
- **ZL/ZR**: Adjust value ±10
- **D-Pad UP/DOWN**: Adjust value ±1
- **A**: Confirm and connect
- **HOME (hold)**: Exit

### During Streaming:
- **Touch screen**: Toggle GamePad display on/off
- **HOME (hold)**: Exit application

## 📦 Building

### Prerequisites:
- devkitPro wiiu-dev packages
- ppc-jansson from devkitpro

### To compile:

**Windows:**
```cmd
COMPILAR_WINDOWS.bat
```

**Linux/macOS:**
```bash
# Create icons folder
mkdir wuhb_custom
cp wuhb/*.png wuhb_custom/

# Configure CMake
mv CMakeLists.txt CMakeLists_original.txt
mv CMakeLists_WiiUViGEmBus.txt CMakeLists.txt

# Build
/opt/devkitpro/portlibs/wiiu/bin/powerpc-eabi-cmake -B build_custom
cmake --build build_custom
```

## 📝 Configuration

The application automatically saves your last used IP in:
```
sd:/wiiu/apps/WiiUViGEmBusController/settings.ini
```

## 🙏 Credits

This application is based on the excellent work of **Crayon** with MiisendU Wii U.

**Original project:**
- GitHub: [https://github.com/Crayon2000/MiisendU-Wii-U](https://github.com/Crayon2000/MiisendU-Wii-U)
- Wiki: [https://wiiubrew.org/wiki/UsendMii](https://wiiubrew.org/wiki/UsendMii)

All credits and thanks go to the original creator. This is a customized version with interface and usability improvements.

## 📄 License

This project maintains the same license as the original project.

## 🔧 Differences from MiisendU

- Black background interface
- Faster and more efficient IP input system
- Touch screen power saving function
- Customized texts and interface
- Updated name and branding

## 🚀 Usage

1. Install the application on your Wii U
2. Make sure you have a UDP server listening on your PC (default port 4242)
3. Run the application from Homebrew Launcher
4. Enter your PC's IP using the improved controls
5. Enjoy streaming your controllers!

## 📊 Speed Comparison

**Example: Changing IP from 192.168.1.1 to 192.168.1.100**

- **Original MiisendU**: ~119 button presses
- **WiiUViGEmBus**: ~21 button presses
- **Result**: 5.6x faster! ⚡

## 📚 Documentation

- **English**: [README_WiiUViGEmBus.md](README_WiiUViGEmBus.md)
- **Español**: [LEEME.md](LEEME.md)
- **Quick Start**: [INICIO_RAPIDO.md](INICIO_RAPIDO.md)
- **Build Instructions**: [BUILD_INSTRUCTIONS.md](BUILD_INSTRUCTIONS.md)
- **Changes**: [CHANGES.md](CHANGES.md)

---

**Version:** 1.0.0  
**Based on:** MiisendU Wii U v1.4.0 by Crayon
