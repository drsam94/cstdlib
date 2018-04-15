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
