#include "console.h"

#include <coreinit/memheap.h>
#include <coreinit/cache.h>
#include <coreinit/memfrmheap.h>
#include <coreinit/memory.h>
#include <coreinit/screen.h>
#include <proc_ui/procui.h>

static const uint32_t CONSOLE_FRAME_HEAP_TAG = 0x000DECAF;

static void *sBufferTV = NULL;
static void *sBufferDRC = NULL;
static uint32_t sBufferSizeTV = 0;
static uint32_t sBufferSizeDRC = 0;
static bool sConsoleHasForeground = true;
static uint32_t consoleColor = 0x000000FF; // Black background

static uint32_t ConsoleProcCallbackAcquired(void *context)
{
   MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);
   MEMRecordStateForFrmHeap(heap, CONSOLE_FRAME_HEAP_TAG);

   if(sBufferSizeTV > 0) {
      sBufferTV = MEMAllocFromFrmHeapEx(heap, sBufferSizeTV, 4);
   }

   if(sBufferSizeDRC > 0) {
      sBufferDRC = MEMAllocFromFrmHeapEx(heap, sBufferSizeDRC, 4);
   }

   sConsoleHasForeground = true;
   OSScreenSetBufferEx(SCREEN_TV, sBufferTV);
   OSScreenSetBufferEx(SCREEN_DRC, sBufferDRC);
   return 0;
}

static uint32_t ConsoleProcCallbackReleased(void *context)
{
   MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);
   MEMFreeByStateToFrmHeap(heap, CONSOLE_FRAME_HEAP_TAG);
   sConsoleHasForeground = false;
   return 0;
}

void ConsoleInit()
{
   OSScreenInit();
   sBufferSizeTV = OSScreenGetBufferSizeEx(SCREEN_TV);
   sBufferSizeDRC = OSScreenGetBufferSizeEx(SCREEN_DRC);

   ConsoleProcCallbackAcquired(NULL);
   OSScreenEnableEx(SCREEN_TV, true);
   OSScreenEnableEx(SCREEN_DRC, true);

   ProcUIRegisterCallback(PROCUI_CALLBACK_ACQUIRE, ConsoleProcCallbackAcquired, NULL, 100);
   ProcUIRegisterCallback(PROCUI_CALLBACK_RELEASE, ConsoleProcCallbackReleased, NULL, 100);
}

void ConsoleFree()
{
   if(sConsoleHasForeground == true) {
      OSScreenShutdown();
      ConsoleProcCallbackReleased(NULL);
   }
}

void ConsoleSetColor(uint32_t color)
{
   consoleColor = color;
}

bool ConsoleDrawStart()
{
   if(sConsoleHasForeground == false) {
      return false;
   }

    OSScreenClearBufferEx(SCREEN_TV, consoleColor);
    OSScreenClearBufferEx(SCREEN_DRC, consoleColor);

    return true;
}

void ConsoleDrawEnd()
{
    DCFlushRange(sBufferTV, sBufferSizeTV);
    DCFlushRange(sBufferDRC, sBufferSizeDRC);
    OSScreenFlipBuffersEx(SCREEN_TV);
    OSScreenFlipBuffersEx(SCREEN_DRC);
}
