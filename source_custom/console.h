#pragma once
#include <wut.h>

#ifdef __cplusplus
extern "C" {
#endif

void ConsoleInit();
void ConsoleFree();
void ConsoleSetColor(uint32_t color);
bool ConsoleDrawStart();
void ConsoleDrawEnd();
void ConsoleDrawEndDRCOnly();

#ifdef __cplusplus
}
#endif
