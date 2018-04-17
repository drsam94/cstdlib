#pragma once

#include "string.h"
#include "gtest/gtest.h"
#include <cstring>
#include <limits>
#include <random>

TEST(strTest, strcpy1) {
    char dst[BUFSIZ];
    char dst2[BUFSIZ];

    auto reset = [&]() {
        ::memset(dst, 1, 100);
        ::memset(dst2, 2, 100);
    };
    reset();

    const char hello[] = "Hello, world\n";
    EXPECT_EQ(dst, ::strcpy(dst, hello));
    EXPECT_EQ(dst2, sd::strcpy(dst2, hello));
    EXPECT_STREQ(dst, dst2);

    reset();
    const char empty[] = "";
    EXPECT_EQ(dst, ::strcpy(dst, empty));
    EXPECT_EQ(dst2, sd::strcpy(dst2, empty));
    EXPECT_STREQ(dst, dst2);
}

TEST(strTest, strncpy1) {
    char dst[BUFSIZ];
    char dst2[BUFSIZ];

    auto reset = [&]() {
        ::memset(dst, 1, 100);
        ::memset(dst2, 2, 100);
    };

    reset();
    const char hello[] = "Hello, world\n";
    EXPECT_EQ(dst, ::strncpy(dst, hello, sizeof(hello)));
    EXPECT_EQ(dst2, sd::strncpy(dst2, hello, sizeof(hello)));
    EXPECT_STREQ(dst, dst2);

    reset();
    const char empty[] = "";
    EXPECT_EQ(dst, ::strncpy(dst, empty, sizeof(empty)));
    EXPECT_EQ(dst2, sd::strncpy(dst2, empty, sizeof(empty)));
    EXPECT_STREQ(dst, dst2);

    reset();
    size_t len = 5;
    EXPECT_EQ(dst, ::strncpy(dst, hello, len));
    EXPECT_EQ(dst2, sd::strncpy(dst2, hello, len));
    EXPECT_EQ(0, ::memcmp(dst, dst2, len));

    reset();
    const char abc[] = "abc";
    len = 73;
    EXPECT_EQ(dst, ::strncpy(dst, abc, len));
    EXPECT_EQ(dst2, sd::strncpy(dst2, abc, len));
    EXPECT_EQ(0, ::memcmp(dst, dst2, len));
}

TEST(strTest, strcat1) {
    char dst[BUFSIZ];
    char dst2[BUFSIZ];

    auto reset = [&]() {
        ::memset(dst, 1, 100);
        ::memset(dst2, 2, 100);
        *dst = '\0';
        *dst2 = '\0';
    };

    reset();
    EXPECT_EQ(dst, ::strcat(dst, "Hello, "));
    EXPECT_EQ(dst, ::strcat(dst, "World!\n"));
    EXPECT_EQ(dst2, sd::strcat(dst2, "Hello, "));
    EXPECT_EQ(dst2, sd::strcat(dst2, "World!\n"));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strcat(dst, ""));
    EXPECT_EQ(dst2, sd::strcat(dst2, ""));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strcat(::strcat(::strcat(dst, "a"), "b"), "c"));
    EXPECT_EQ(dst2, sd::strcat(sd::strcat(sd::strcat(dst2, "a"), "b"), "c"));
    EXPECT_STREQ(dst, dst2);
}

TEST(strTest, strncat1) {
    // strncat should act exactly like strcat if it has n >= strlen(src)
    char dst[BUFSIZ];
    char dst2[BUFSIZ];

    auto reset = [&]() {
        ::memset(dst, 1, 100);
        ::memset(dst2, 2, 100);
        *dst = '\0';
        *dst2 = '\0';
    };

    reset();
    EXPECT_EQ(dst, ::strncat(dst, "Hello, ", sizeof("Hello, ")));
    EXPECT_EQ(dst, ::strncat(dst, "World!\n", sizeof("World!\n")));
    EXPECT_EQ(dst2, sd::strncat(dst2, "Hello, ", sizeof("Hello, ")));
    EXPECT_EQ(dst2, sd::strncat(dst2, "World!\n", sizeof("World!\n")));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strncat(dst, "Hello, ", sizeof("Hello, ") - 1));
    EXPECT_EQ(dst, ::strncat(dst, "World!\n", sizeof("World!\n") - 1));
    EXPECT_EQ(dst2, sd::strncat(dst2, "Hello, ", sizeof("Hello, ") - 1));
    EXPECT_EQ(dst2, sd::strncat(dst2, "World!\n", sizeof("World!\n") - 1));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strncat(dst, "", 0));
    EXPECT_EQ(dst2, sd::strncat(dst2, "", 0));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strncat(dst, "", 1));
    EXPECT_EQ(dst2, sd::strncat(dst2, "", 1));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strncat(::strncat(::strncat(dst, "a", 100), "b", 100), "c",
                             100));
    EXPECT_EQ(dst2,
              sd::strncat(sd::strncat(sd::strncat(dst2, "a", 100), "b", 100),
                          "c", 100));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst,
              ::strncat(::strncat(::strncat(dst, "a", 1), "b", 1), "c", 1));
    EXPECT_EQ(dst2, sd::strncat(sd::strncat(sd::strncat(dst2, "a", 1), "b", 1),
                                "c", 1));
    EXPECT_STREQ(dst, dst2);
}

TEST(strTest, strcat2) {
    char dst[BUFSIZ];
    char dst2[BUFSIZ];

    auto reset = [&]() {
        ::memset(dst, 1, 100);
        ::memset(dst2, 2, 100);
        *dst = '\0';
        *dst2 = '\0';
    };

    reset();
    EXPECT_EQ(dst, ::strncat(dst, "Hello, ", 3));
    EXPECT_EQ(dst, ::strncat(dst, "World!\n", 4));
    EXPECT_EQ(dst2, sd::strncat(dst2, "Hello, ", 3));
    EXPECT_EQ(dst2, sd::strncat(dst2, "World!\n", 4));
    EXPECT_STREQ(dst, dst2);

    reset();
    EXPECT_EQ(dst, ::strncat(dst, "Hello", 0));
    EXPECT_EQ(dst2, sd::strncat(dst2, "World", 0));
    EXPECT_STREQ(dst, dst2);
}

namespace {
inline int sign(int x) {
    if (x < 0) {
        return -1;
    } else if (x > 0) {
        return 1;
    } else {
        return 0;
    }
}
}

#define EXPECT_SIGN(x, y) EXPECT_EQ(sign(x), sign(y))
TEST(strTest, strcmp1) {
    EXPECT_SIGN(::strcmp("Hello", "World"), sd::strcmp("Hello", "World"));
    EXPECT_SIGN(::strcmp("Hello", "Hel"), sd::strcmp("Hello", "Hel"));
    EXPECT_SIGN(::strcmp("Wor", "World"), sd::strcmp("Wor", "World"));
    EXPECT_SIGN(::strcmp("abc", "abd"), sd::strcmp("abc", "abd"));
    EXPECT_SIGN(::strcmp("", ""), sd::strcmp("", ""));
    EXPECT_SIGN(::strcmp("", "abc"), sd::strcmp("", "abc"));
    EXPECT_SIGN(::strcmp("abc", ""), sd::strcmp("abc", ""));
}

TEST(strTest, strncmp1) {
    EXPECT_SIGN(::strncmp("Hello", "World", 5),
                sd::strncmp("Hello", "World", 5));
    EXPECT_SIGN(::strncmp("Hello", "World", 6),
                sd::strncmp("Hello", "World", 6));
    EXPECT_SIGN(::strncmp("Hello", "Hel", 5), sd::strncmp("Hello", "Hel", 5));
    EXPECT_SIGN(::strncmp("Wor", "World", 5), sd::strncmp("Wor", "World", 5));
    EXPECT_SIGN(::strncmp("abc", "abd", 3), sd::strncmp("abc", "abd", 3));
    EXPECT_SIGN(::strncmp("", "", 0), sd::strncmp("", "", 0));
    EXPECT_SIGN(::strncmp("", "", 1), sd::strncmp("", "", 1));
    EXPECT_SIGN(::strncmp("", "abc", 3), sd::strncmp("", "abc", 3));
    EXPECT_SIGN(::strncmp("abc", "", 3), sd::strncmp("abc", "", 3));
}

TEST(strTest, strncmp2) {
    EXPECT_SIGN(::strncmp("Hello", "World", 2),
                sd::strncmp("Hello", "World", 2));
    EXPECT_SIGN(::strncmp("Hello", "World", 1),
                sd::strncmp("Hello", "World", 1));
    EXPECT_SIGN(::strncmp("Hello", "Hel", 3), sd::strncmp("Hello", "Hel", 3));
    EXPECT_SIGN(::strncmp("Hello", "Hel", 4), sd::strncmp("Hello", "Hel", 4));
    EXPECT_SIGN(::strncmp("Wor", "World", 3), sd::strncmp("Wor", "World", 3));
    EXPECT_SIGN(::strncmp("Wor", "World", 4), sd::strncmp("Wor", "World", 4));
    EXPECT_SIGN(::strncmp("abc", "abd", 2), sd::strncmp("abc", "abd", 2));
    EXPECT_SIGN(::strncmp("", "abc", 0), sd::strncmp("", "abc", 0));
}

TEST(strTest, strcasecmp1) {
    EXPECT_SIGN(::strcasecmp("Hello", "World"), sd::strcmp("Hello", "World"));
    EXPECT_SIGN(::strcasecmp("Hello", "Hel"), sd::strcmp("Hello", "Hel"));
    EXPECT_SIGN(::strcasecmp("Wor", "World"), sd::strcmp("Wor", "World"));
    EXPECT_SIGN(::strcasecmp("abc", "abd"), sd::strcmp("abc", "abd"));
    EXPECT_SIGN(::strcasecmp("", ""), sd::strcmp("", ""));
    EXPECT_SIGN(::strcasecmp("", "abc"), sd::strcmp("", "abc"));
    EXPECT_SIGN(::strcasecmp("abc", ""), sd::strcmp("abc", ""));
}

TEST(strTest, strcasecmp2) {
    EXPECT_SIGN(::strcasecmp("HELLO", "hello"),
                sd::strcasecmp("HELLO", "hello"));
    EXPECT_SIGN(::strcasecmp("HeLlO", "HeL"), sd::strcasecmp("HeLlO", "HeL"));
    EXPECT_SIGN(::strcasecmp("hEl", "hElLo"), sd::strcasecmp("hEl", "hElLo"));
}

TEST(strTest, strncasecmp1) {
    EXPECT_SIGN(::strncasecmp("Hello", "World", 5),
                sd::strncasecmp("Hello", "World", 5));
    EXPECT_SIGN(::strncasecmp("Hello", "World", 6),
                sd::strncasecmp("Hello", "World", 6));
    EXPECT_SIGN(::strncasecmp("Hello", "Hel", 5),
                sd::strncmp("Hello", "Hel", 5));
    EXPECT_SIGN(::strncasecmp("Wor", "World", 5),
                sd::strncmp("Wor", "World", 5));
    EXPECT_SIGN(::strncasecmp("abc", "abd", 3), sd::strncmp("abc", "abd", 3));
    EXPECT_SIGN(::strncasecmp("", "", 0), sd::strncmp("", "", 0));
    EXPECT_SIGN(::strncasecmp("", "", 1), sd::strncmp("", "", 1));
    EXPECT_SIGN(::strncasecmp("", "abc", 3), sd::strncmp("", "abc", 3));
    EXPECT_SIGN(::strncasecmp("abc", "", 3), sd::strncmp("abc", "", 3));
}

TEST(strTest, strncasecmp2) {
    EXPECT_SIGN(::strncasecmp("Hello", "World", 2),
                sd::strncasecmp("Hello", "World", 2));
    EXPECT_SIGN(::strncasecmp("Hello", "World", 1),
                sd::strncasecmp("Hello", "World", 1));
    EXPECT_SIGN(::strncasecmp("Hello", "Hel", 3),
                sd::strncmp("Hello", "Hel", 3));
    EXPECT_SIGN(::strncasecmp("Hello", "Hel", 4),
                sd::strncmp("Hello", "Hel", 4));
    EXPECT_SIGN(::strncasecmp("Wor", "World", 3),
                sd::strncmp("Wor", "World", 3));
    EXPECT_SIGN(::strncasecmp("abc", "abd", 2), sd::strncmp("abc", "abd", 2));
    EXPECT_SIGN(::strncasecmp("", "abc", 0), sd::strncmp("", "abc", 0));
}

TEST(strTest, strncasecmp3) {
    EXPECT_SIGN(::strncasecmp("HELLO", "hello", 5),
                sd::strncasecmp("HELLO", "hello", 5));
    EXPECT_SIGN(::strncasecmp("HeLlO", "HeL", 3),
                sd::strncasecmp("HeLlO", "HeL", 3));
    EXPECT_SIGN(::strncasecmp("hEl", "hElLo", 4),
                sd::strncasecmp("hEl", "hElLo", 4));
    EXPECT_SIGN(::strncasecmp("HeLlO", "HeL", 3),
                sd::strncasecmp("HeLlO", "HeL", 3));
    EXPECT_SIGN(::strncasecmp("hEl", "hElLo", 4),
                sd::strncasecmp("hEl", "hElLo", 4));
    EXPECT_SIGN(::strncasecmp("HELLW", "hellx", 4),
                sd::strncasecmp("HELLW", "hellx", 4));
    EXPECT_SIGN(::strncasecmp("HeL$O", "HeL!O", 4),
                sd::strncasecmp("HeL$O", "HeL!O", 4));
    EXPECT_SIGN(::strncasecmp("$$l", "$$lLo", 3),
                sd::strncasecmp("$$l", "$$lLo", 3));
}
TEST(strTest, strchr1) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strchr(hello, 'e'), sd::strchr(hello, 'e'));
    EXPECT_EQ(::strchr(hello, '\n'), sd::strchr(hello, '\n'));
    EXPECT_EQ(::strchr(hello, '\0'), sd::strchr(hello, '\0'));
    EXPECT_EQ(::strchr(hello, 'z'), sd::strchr(hello, 'z'));

    EXPECT_EQ(::strchr("", 'a'), sd::strchr("", 'a'));
    EXPECT_EQ(::strchr("", '\0'), sd::strchr("", '\0'));
}
TEST(strTest, strrchr1) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strrchr(hello, 'e'), sd::strrchr(hello, 'e'));
    EXPECT_EQ(::strrchr(hello, '\n'), sd::strrchr(hello, '\n'));
    EXPECT_EQ(::strrchr(hello, '\0'), sd::strrchr(hello, '\0'));
    EXPECT_EQ(::strrchr(hello, 'z'), sd::strrchr(hello, 'z'));

    EXPECT_EQ(::strrchr("", 'a'), sd::strrchr("", 'a'));
    EXPECT_EQ(::strrchr("", '\0'), sd::strrchr("", '\0'));
}
TEST(strTest, strrchr2) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strrchr(hello, 'l'), sd::strrchr(hello, 'l'));
    const char zs[] = "ZZAZZ";
    EXPECT_EQ(::strrchr(zs, 'Z'), sd::strrchr(zs, 'Z'));
    const char as[] = "AAAAAAAAAAAAAAA";
    EXPECT_EQ(::strrchr(as, 'A'), sd::strrchr(as, 'A'));
}
TEST(strTest, strchrnul1) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strchrnul(hello, 'e'), sd::strchrnul(hello, 'e'));
    EXPECT_EQ(::strchrnul(hello, '\n'), sd::strchrnul(hello, '\n'));
    EXPECT_EQ(::strchrnul(hello, '\0'), sd::strchrnul(hello, '\0'));
    EXPECT_EQ(::strchrnul(hello, 'z'), sd::strchrnul(hello, 'z'));

    EXPECT_EQ(::strchrnul("", 'a'), sd::strchrnul("", 'a'));
    EXPECT_EQ(::strchrnul("", '\0'), sd::strchrnul("", '\0'));
}
TEST(strTest, strpbrk1) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strpbrk(hello, "e"), sd::strpbrk(hello, "e"));
    EXPECT_EQ(::strpbrk(hello, "\n"), sd::strpbrk(hello, "\n"));
    EXPECT_EQ(::strpbrk(hello, ""), sd::strpbrk(hello, ""));
    EXPECT_EQ(::strpbrk(hello, "z"), sd::strpbrk(hello, "z"));

    EXPECT_EQ(::strpbrk("", "a"), sd::strpbrk("", "a"));
    EXPECT_EQ(::strpbrk("", ""), sd::strpbrk("", ""));
}
TEST(strTest, strpbrk2) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strpbrk(hello, "oW!"), sd::strpbrk(hello, "oW!"));
    EXPECT_EQ(::strpbrk(hello, "!Wo"), sd::strpbrk(hello, "!Wo"));
    EXPECT_EQ(::strpbrk(hello, "$%^"), sd::strpbrk(hello, "$%^"));
    EXPECT_EQ(::strpbrk(hello, "$%^d"), sd::strpbrk(hello, "$%^d"));
}
TEST(strTest, strstr1) {
    const char hello[] = "Hello, World!\n";
    EXPECT_EQ(::strstr(hello, "e"), sd::strstr(hello, "e"));
    EXPECT_EQ(::strstr(hello, "\n"), sd::strstr(hello, "\n"));
    EXPECT_EQ(::strstr(hello, ""), sd::strstr(hello, ""));
    EXPECT_EQ(::strstr(hello, "z"), sd::strstr(hello, "z"));

    EXPECT_EQ(::strstr("", "a"), sd::strstr("", "a"));
    EXPECT_EQ(::strstr("", ""), sd::strstr("", ""));
}
TEST(srtRest, strstr2) {
    const char s[] = "gggaaaggggcat";
    EXPECT_EQ(::strstr(s, "ggg"), sd::strstr(s, "ggg"));
    EXPECT_EQ(::strstr(s, "gggg"), sd::strstr(s, "gggg"));
    EXPECT_EQ(::strstr(s, "ggggg"), sd::strstr(s, "ggggg"));
    EXPECT_EQ(::strstr(s, "gaaag"), sd::strstr(s, "gaaag"));
    EXPECT_EQ(::strstr(s, "cat"), sd::strstr(s, "cat"));
}

#undef EXPECT_SIGN
