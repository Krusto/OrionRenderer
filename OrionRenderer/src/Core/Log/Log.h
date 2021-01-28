#pragma once
#include <stdio.h>
#include <cstdarg>
#include <iostream>

#define RESET_COLOR "\033[0m"+
#define BLACK_COLOR "\033[0;30m"+
#define RED_COLOR "\033[0;31m"+
#define GREEN_COLOR "\033[0;32m"+
#define YELLOW_COLOR "\033[0;33m"+
#define BLUE_COLOR "\033[0;34m"+
#define MAGENTA_COLOR "\033[0;35m"+
#define CYAN_COLOR "\033[0;36m"+
#define WHITE_COLOR "\033[0;37m"+

constexpr const char* colorValues[]{
    "\033[0m",
    "\033[0;30m",
    "\033[0;31m",
    "\033[0;32m",
    "\033[0;33m",
    "\033[0;34m",
    "\033[0;35m",
    "\033[0;36m",
    "\033[0;37m"
};
constexpr const char* colorTags[]{
    "{RESET}",
    "{BLACK}",
    "{RED}",
    "{GREEN}",
    "{YELLOW}",
    "{BLUE}",
    "{MAGENTA}",
    "{CYAN}",
    "{WHITE}"
};

#define OrionLog(format,...) DebugLog(format,__VA_ARGS__)
#define DebugLog(format,...) Print(Log("{GREEN} DEBUG INFO: {WHITE}", "{RESET}\n\r",format, __VA_ARGS__));
#define DebugError(format,...) Print(Log("{RED} ERROR INFO: {YELLOW}", "{RESET}\n\r",format, __VA_ARGS__));

std::string Log(const char* prefix, const char* suffix, const char* Format, ...);

#define OrionAssert(expr,format,...) if(!(expr)){OrionLog(format,__VA_ARGS__);}

void Print(std::string data);