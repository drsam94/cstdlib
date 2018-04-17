#include "string.h"
using std::byte;

// All of these methods are intentionally implemented with the following
// constraints:
// 1: The code is written in non-warning ISO C++
// 2: Each implementation uses no standard library functions
// 3: No implementations share code or call one another
namespace sd {
void* memcpy(void* dest, const void* src, size_t n) {
    byte* bdest = static_cast<byte*>(dest);
    const byte* bsrc = static_cast<const byte*>(src);
    const byte* end = bdest + n;
    while (bdest != end) {
        *bdest++ = *bsrc++;
    }
    return dest;
}
void* memccpy(void* dest, const void* src, int c, size_t n) {
    byte* bdest = static_cast<byte*>(dest);
    const byte* bsrc = static_cast<const byte*>(src);
    const byte* end = bdest + n;
    while (bdest != end) {
        *bdest = *bsrc++;
        if (*bdest++ == static_cast<byte>(c)) {
            return static_cast<void*>(bdest);
        }
    }
    return nullptr;
}
void* memmove(void* dest, const void* src, size_t n) {
    byte* bdest = static_cast<byte*>(dest);
    const byte* bsrc = static_cast<const byte*>(src);
    const byte* end = bsrc + n;
    if (dest > src && end > dest) {
        // We have to go in reverse
        bdest += n - 1;
        bsrc += n - 1;
        end -= n + 1;
        while (bsrc != end) {
            *bdest-- = *bsrc--;
        }
    } else {
        // we can do the regular order
        while (bsrc != end) {
            *bdest++ = *bsrc++;
        }
    }
    return dest;
}
char* strcpy(char* dest, const char* src) {
    char* dst = dest;
    while ((*dst++ = *src++))
        ;
    return dest;
}
char* strncpy(char* dest, const char* src, size_t n) {
    const char* end = dest + n;
    char* dst = dest;
    while (dst != end && (*dst++ = *src++))
        ;
    while (dst != end) {
        *dst++ = '\0';
    }
    return dest;
}
char* strcat(char* dest, const char* src) {
    char* dst = dest;
    while (*dst)
        ++dst;
    while ((*dst++ = *src++))
        ;
    return dest;
}
char* strncat(char* dest, const char* src, size_t n) {
    char* dst = dest;
    while (*dst)
        ++dst;
    for (size_t i = 0; i < n; ++i) {
        if (!(*dst++ = *src++)) {
            return dest;
        }
    }
    *dst = '\0';
    return dest;
}
int strcmp(const char* s1, const char* s2) {
    int ret = 0;
    while (!(ret = *s1++ - *s2) && *s2++)
        ;
    return ret;
}
int strncmp(const char* s1, const char* s2, size_t n) {
    int ret = 0;
    const char* end = s1 + n;
    while (s1 != end && !(ret = *s1++ - *s2) && *s2++)
        ;
    return ret;
}
int strcasecmp(const char* s1, const char* s2) {
    int ret = 0;
    do {
        char a = *s1++;
        char b = *s2;
        if (a >= 'A' && a <= 'Z') {
            a += 'a' - 'A';
        }
        if (b >= 'A' && b <= 'Z') {
            b += 'a' - 'A';
        }
        ret = a - b;
    } while (!ret && *s2++);
    return ret;
}
int strncasecmp(const char* s1, const char* s2, size_t n) {
    int ret = 0;
    const char* end = s1 + n;
    while (!ret && s1 != end) {
        char a = *s1++;
        char b = *s2;
        if (a >= 'A' && a <= 'Z') {
            a += 'a' - 'A';
        }
        if (b >= 'A' && b <= 'Z') {
            b += 'a' - 'A';
        }
        ret = a - b;
        if (!*s2++) {
            break;
        }
    }
    return ret;
}
char* strchr(const char* s, int c) {
    while (*s != c) {
        if (!*s++)
            return nullptr;
    }
    return const_cast<char*>(s);
}
char* strrchr(const char* s, int c) {
    const char* ret = nullptr;
    do {
        if (*s == c) {
            ret = s;
        }
    } while (*s++);
    return const_cast<char*>(ret);
}
char* strchrnul(const char* s, int c) {
    while (*s != c && *s) {
        ++s;
    }
    return const_cast<char*>(s);
}
char* strpbrk(const char* s, const char* accept) {
    do {
        const char* a = accept;
        while (*a) {
            if (*s == *a++) {
                return const_cast<char*>(s);
            }
        }
    } while (*s++);
    return nullptr;
}
char* strstr(const char* haystack, const char* needle) {
    const char* h = haystack;
    do {
        const char* s = h;
        const char* n = needle;
        do {
            if (!*n) {
                return const_cast<char*>(h);
            }
        } while (*s++ == *n++);
    } while (*h++);
    return nullptr;
}
} // namespace sd
