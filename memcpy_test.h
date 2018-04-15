#pragma once

#include "string.h"
#include "gtest/gtest.h"
#include <cstring>
#include <limits>
#include <random>

TEST(memcpyTest, memcpy1) {
    std::mt19937 mt(0);
    std::uniform_int_distribution<char> uniform(
        std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
    char dst[BUFSIZ];
    char dst2[BUFSIZ];
    char src[BUFSIZ];
    auto reset = [&]() {
        for (size_t i = 0; i < 255; ++i) {
            dst[i] = uniform(mt);
            dst2[i] = uniform(mt);
            src[i] = uniform(mt);
        }
    };
    reset();

    size_t size = 10;
    EXPECT_EQ(dst, ::memcpy(dst, src, size));
    EXPECT_EQ(dst2, sd::memcpy(dst2, src, size));
    EXPECT_EQ(0, ::memcmp(dst, dst2, size));

    reset();
    size = 200;
    EXPECT_EQ(dst, ::memcpy(dst, src, size));
    EXPECT_EQ(dst2, sd::memcpy(dst2, src, size));
    EXPECT_EQ(0, ::memcmp(dst, dst2, size));

    reset();
    size = 50;
    EXPECT_EQ(dst + 20, ::memcpy(dst + 20, src + 10, size));
    EXPECT_EQ(dst2 + 20, sd::memcpy(dst2 + 20, src + 10, size));
    EXPECT_EQ(0, ::memcmp(dst + 20, dst2 + 20, size));

    // This is a bad use of memcpy, but it should work
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wnonnull"
#endif
    EXPECT_EQ(::memcpy(nullptr, nullptr, 0), sd::memcpy(nullptr, nullptr, 0));
    EXPECT_EQ(::memcpy(dst, nullptr, 0), sd::memcpy(dst, nullptr, 0));
    EXPECT_EQ(::memcpy(nullptr, src, 0), sd::memcpy(nullptr, src, 0));
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
}

TEST(memcpyTest, memccpy1) {
    char dst[BUFSIZ];
    char dst2[BUFSIZ];

    auto reset = [&]() {
        ::memset(dst, 0, 100);
        ::memset(dst2, 1, 100);
    };
    reset();

    const char src1[] = "123456789123456789";
    EXPECT_EQ(::memccpy(dst, src1, 'a', sizeof(src1)),
              sd::memccpy(dst2, src1, 'a', sizeof(src1)));
    EXPECT_EQ(0, ::memcmp(dst, dst2, sizeof(src1)));

    reset();
    ptrdiff_t len =
        static_cast<char*>(::memccpy(dst, src1, '9', sizeof(src1))) - dst;
    EXPECT_EQ(static_cast<char*>(sd::memccpy(dst2, src1, '9', sizeof(src1))) -
                  dst2,
              len);
    EXPECT_EQ(0, ::memcmp(dst, dst2, len));

    reset();
    const char src2[] = "abcdefghijklmnopqrstuvwxyz";

    len = static_cast<char*>(::memccpy(dst, src2, 'z', sizeof(src2) - 1)) - dst;
    EXPECT_EQ(
        static_cast<char*>(sd::memccpy(dst2, src2, 'z', sizeof(src2) - 1)) -
            dst2,
        len);
    EXPECT_EQ(0, ::memcmp(dst, dst2, len));
}

TEST(memcpyTest, memmove1) {
    // memmove should be able to do everything memcpy can do, and more; so let's
    // first run it through the same test of tests as memcpy
    std::mt19937 mt(0);
    std::uniform_int_distribution<char> uniform(
        std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
    char dst[BUFSIZ];
    char dst2[BUFSIZ];
    char src[BUFSIZ];
    auto reset = [&]() {
        for (size_t i = 0; i < 255; ++i) {
            dst[i] = uniform(mt);
            dst2[i] = uniform(mt);
            src[i] = uniform(mt);
        }
    };
    reset();

    size_t size = 10;
    EXPECT_EQ(dst, ::memmove(dst, src, size));
    EXPECT_EQ(dst2, sd::memmove(dst2, src, size));
    EXPECT_EQ(0, ::memcmp(dst, dst2, size));

    reset();
    size = 200;
    EXPECT_EQ(dst, ::memmove(dst, src, size));
    EXPECT_EQ(dst2, sd::memmove(dst2, src, size));
    EXPECT_EQ(0, ::memcmp(dst, dst2, size));

    reset();
    size = 50;
    EXPECT_EQ(dst + 20, ::memmove(dst + 20, src + 10, size));
    EXPECT_EQ(dst2 + 20, sd::memmove(dst2 + 20, src + 10, size));
    EXPECT_EQ(0, ::memcmp(dst + 20, dst2 + 20, size));

    // This is a bad use of memcpy, but it should work
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wnonnull"
#endif
    EXPECT_EQ(::memmove(nullptr, nullptr, 0), sd::memmove(nullptr, nullptr, 0));
    EXPECT_EQ(::memmove(dst, nullptr, 0), sd::memmove(dst, nullptr, 0));
    EXPECT_EQ(::memmove(nullptr, src, 0), sd::memmove(nullptr, src, 0));
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
}

TEST(memcpyTest, memmove2) {
    // Memmove with overlapping regions
    char buf[BUFSIZ];
    char buf2[BUFSIZ];
    std::mt19937 mt(0);
    std::uniform_int_distribution<char> uniform(
        std::numeric_limits<char>::min(), std::numeric_limits<char>::max());
    auto reset = [&]() {
        for (size_t i = 0; i < 255; ++i) {
            buf[i] = buf2[i] = uniform(mt);
        }
    };
    reset();
    size_t len = 20;
    EXPECT_EQ(buf, ::memmove(buf, buf + 10, len));
    EXPECT_EQ(buf2, sd::memmove(buf2, buf2 + 10, len));
    EXPECT_EQ(0, ::memcmp(buf, buf2, len + 10));

    reset();
    EXPECT_EQ(buf + 10, ::memmove(buf + 10, buf, len));
    EXPECT_EQ(buf2 + 10, sd::memmove(buf2 + 10, buf2, len));
    EXPECT_EQ(0, ::memcmp(buf, buf2, len + 10));

    reset();
    EXPECT_EQ(buf, ::memmove(buf, buf, len));
    EXPECT_EQ(buf2, sd::memmove(buf2, buf2, len));
    EXPECT_EQ(0, ::memcmp(buf, buf2, len));
}
