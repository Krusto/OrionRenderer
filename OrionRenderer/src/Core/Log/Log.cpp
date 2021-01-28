#include "Log.h"

#include <stdio.h>
#include <cstdarg>
#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
/*
void Log(std::string& output,const char* format ,...)
{
    va_list args;
    va_start(args, format);
    uint32_t it = 0;

    while (format[it] != '\0') {
        if (format[it] == '{') {
            uint32_t count = 0;
            std::string currentTag = "{";
            it++;
            while (format[it] != '}') {
                currentTag += format[it];
                it++;
            }
            currentTag += "}";
            if (format[it] == '}') {
                for (uint32_t i = 0; i < 9; i++) {
                    if (colorTags[i] == currentTag) {
                        output += colorValues[i];
                    }
                }
            }
        }
        else if (format[it] == '%') {
            it++;
            if (format[it] == 'f') {
                double d = va_arg(args, double);
                output += std::to_string(d);
            }
            else if (format[it] == 'i') {
                int c = va_arg(args, int);
                output += std::to_string(c);
            }
            else if (format[it] == 's') {
                std::string s = std::string(va_arg(args, const char*));
                output += s;
            }

        }
        else {
            output += format[it];
        }
        it++;
    }
    std::cout << output;
    va_end(args);
}

void DebugLog(const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);

    std::string customFormat = "{GREEN} DEBUG INFO: {WHITE}" + std::string(format) + "{RESET}";

    std::string output;

    Log(output,format, args);


    va_end(args);
}
*/

std::string Log(const char* prefix, const char* suffix, const char* Format, ...)
{
    va_list args;
    va_start(args, Format);
    uint32_t it = 0;
    std::string output;
    std::string format = std::string(prefix) + std::string(Format) + std::string(suffix);
    while (format[it] != '\0') {
        if (format[it] == '{') {
            uint32_t count = 0;
            std::string currentTag = "{";
            it++;
            while (format[it] != '}') {
                currentTag += format[it];
                it++;
            }
            currentTag += "}";
            if (format[it] == '}') {
                for (uint32_t i = 0; i < 9; i++) {
                    if (colorTags[i] == currentTag) {
                        output += colorValues[i];
                    }
                }
            }
        }
        else if (format[it] == '%') {
            it++;
            if (format[it] == 'f') {
                double d = va_arg(args, double);
                output += std::to_string(d);
            }
            else if (format[it] == 'd') {
                double d = va_arg(args, double);
                output += std::to_string(d);
            }
            else if (format[it] == 'i') {
                int c = va_arg(args, int);
                output += std::to_string(c);
            }
            else if (format[it] == 's') {
                std::string s = std::string(va_arg(args, const char*));
                output += s;
            }
            else if (format[it] == '>') {
                it++;
                std::string::size_type sz;
                int numSpaces = std::stoi(std::string(1,format[it]),&sz);
                std::string spaces(numSpaces,' ');
                output += spaces;
            }

        }
        else {
            output += format[it];
        }
        it++;
    }
    va_end(args);
    return output;
}

void Print(std::string data)
{
#ifdef _WIN32
        system(("echo " + data).c_str());
#else
        std::cout << std::string(data);
#endif
}
