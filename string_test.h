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
TEST(strTest, strstr2) {
    const char s[] = "gggaaaggggcat";
    EXPECT_EQ(::strstr(s, "ggg"), sd::strstr(s, "ggg"));
    EXPECT_EQ(::strstr(s, "gggg"), sd::strstr(s, "gggg"));
    EXPECT_EQ(::strstr(s, "ggggg"), sd::strstr(s, "ggggg"));
    EXPECT_EQ(::strstr(s, "gaaag"), sd::strstr(s, "gaaag"));
    EXPECT_EQ(::strstr(s, "cat"), sd::strstr(s, "cat"));
}
TEST(strTest, memchr1) {
    const char hello[] = "Hello, World!\n";
    const size_t N = sizeof(hello);
    EXPECT_EQ(::memchr(hello, 'e', N), sd::memchr(hello, 'e', N));
    EXPECT_EQ(::memchr(hello, '\n', N), sd::memchr(hello, '\n', N));
    EXPECT_EQ(::memchr(hello, '\0', N), sd::memchr(hello, '\0', N));
    EXPECT_EQ(::memchr(hello, 'z', N), sd::memchr(hello, 'z', N));

    EXPECT_EQ(::memchr("", 'a', 1), sd::memchr("", 'a', 1));
    EXPECT_EQ(::memchr("", '\0', 1), sd::memchr("", '\0', 1));

    EXPECT_EQ(::memchr(hello, 'e', 2), sd::memchr(hello, 'e', 2));
    EXPECT_EQ(::memchr(hello, '\n', N - 2), sd::memchr(hello, '\n', N - 2));
    EXPECT_EQ(::memchr(hello, '\0', N - 1), sd::memchr(hello, '\0', N - 1));
    EXPECT_EQ(::memchr(hello, 'z', 0), sd::memchr(hello, 'z', 0));

    EXPECT_EQ(::memchr("", 'a', 0), sd::memchr("", 'a', 0));
    EXPECT_EQ(::memchr("", '\0', 0), sd::memchr("", '\0', 0));
}
TEST(strTest, strlen1) {
    EXPECT_EQ(::strlen(""), sd::strlen(""));
    EXPECT_EQ(::strlen("abc"), sd::strlen("abc"));
    EXPECT_EQ(::strlen("Hello, World!\n"), sd::strlen("Hello, World!\n"));
}
