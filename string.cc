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
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(s1);
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(s2);
    while (!(ret = *p1++ - *p2) && *p2++)
        ;
    return ret;
}
int strncmp(const char* s1, const char* s2, size_t n) {
    int ret = 0;
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(s1);
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(s2);
    const unsigned char* end = p1 + n;
    while (p1 != end && !(ret = *p1++ - *p2) && *p2++)
        ;
    return ret;
}
int strcasecmp(const char* s1, const char* s2) {
    int ret = 0;
    do {
        unsigned char a = *s1++;
        unsigned char b = *s2;
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
        unsigned char a = *s1++;
        unsigned char b = *s2;
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
void* memchr(const void* s, int c, size_t n) {
    const char* p = static_cast<const char*>(s);
    for (size_t i = 0; i < n; ++i) {
        if (*p == c) {
            return const_cast<void*>(static_cast<const void*>(p));
        }
        ++p;
    }
    return nullptr;
}
int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* p1 = static_cast<const unsigned char*>(s1);
    const unsigned char* p2 = static_cast<const unsigned char*>(s2);
    for (size_t i = 0; i < n; ++i) {
        if (int v = *p1++ - *p2++; v) {
            return v;
        }
    }
    return 0;
}
void* memset(void* s, int c, size_t n) {
    char* p = static_cast<char*>(s);
    for (size_t i = 0; i < n; ++i) {
        *p = c;
    }
    return s;
}
size_t strlen(const char* s) {
    size_t len = 0;
    while (*s++)
        ++len;
    return len;
}
size_t strspn(const char* s, const char* accept);
size_t strcspn(const char* s, const char* reject);
} // namespace sd
