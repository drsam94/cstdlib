#pragma once
#include <cstddef>

// Various methods from <string.h>
namespace sd {
void* memcpy(void* dest, const void* src, size_t n);
void* memccpy(void* dest, const void* src, int c, size_t n);
void* memmove(void* dest, const void* src, size_t n);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);
// Below functions do not yet have tests written
char* strchr(const char* s, int c);
char* strrchr(const char* s, int c);
char* strchrnul(const char* s, int c);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
int strcasecmp(const char* s1, const char* s2);
int strncasecmp(const char* s1, const char* s2, size_t n);
} // namespace sd
