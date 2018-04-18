#pragma once

#include "string.h"
#include "gtest/gtest.h"
#include <cstring>

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
TEST(cmpTest, strcmp1) {
    EXPECT_SIGN(::strcmp("Hello", "World"), sd::strcmp("Hello", "World"));
    EXPECT_SIGN(::strcmp("Hello", "Hel"), sd::strcmp("Hello", "Hel"));
    EXPECT_SIGN(::strcmp("Wor", "World"), sd::strcmp("Wor", "World"));
    EXPECT_SIGN(::strcmp("abc", "abd"), sd::strcmp("abc", "abd"));
    EXPECT_SIGN(::strcmp("", ""), sd::strcmp("", ""));
    EXPECT_SIGN(::strcmp("", "abc"), sd::strcmp("", "abc"));
    EXPECT_SIGN(::strcmp("abc", ""), sd::strcmp("abc", ""));
}

TEST(cmpTest, strcmp2) {
    const char s1[] = "\x00\xFF\x00\xFF";
    const char s2[] = "\xFF\x00\xFF\x00";
    EXPECT_SIGN(::strcmp(s1, s2), sd::strcmp(s1, s2));
    EXPECT_SIGN(::strcmp(s1, s1), sd::strcmp(s1, s1));
    EXPECT_SIGN(::strcmp(s2, s2), sd::strcmp(s2, s2));
    EXPECT_SIGN(::strcmp(s2, s1), sd::strcmp(s2, s1));
}

TEST(cmpTest, strncmp1) {
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

TEST(cmpTest, strncmp2) {
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

TEST(cmpTest, strncmp3) {
    const char s1[] = "\x00\xFF\x00\xFF";
    const char s2[] = "\xFF\x00\xFF\x00";
    EXPECT_SIGN(::strncmp(s1, s2, 5), sd::strncmp(s1, s2, 5));
    EXPECT_SIGN(::strncmp(s1, s1, 5), sd::strncmp(s1, s1, 5));
    EXPECT_SIGN(::strncmp(s2, s2, 5), sd::strncmp(s2, s2, 5));
    EXPECT_SIGN(::strncmp(s2, s1, 5), sd::strncmp(s2, s1, 5));
}

TEST(cmpTest, strcasecmp1) {
    EXPECT_SIGN(::strcasecmp("Hello", "World"), sd::strcmp("Hello", "World"));
    EXPECT_SIGN(::strcasecmp("Hello", "Hel"), sd::strcmp("Hello", "Hel"));
    EXPECT_SIGN(::strcasecmp("Wor", "World"), sd::strcmp("Wor", "World"));
    EXPECT_SIGN(::strcasecmp("abc", "abd"), sd::strcmp("abc", "abd"));
    EXPECT_SIGN(::strcasecmp("", ""), sd::strcmp("", ""));
    EXPECT_SIGN(::strcasecmp("", "abc"), sd::strcmp("", "abc"));
    EXPECT_SIGN(::strcasecmp("abc", ""), sd::strcmp("abc", ""));
}

TEST(cmpTest, strcasecmp2) {
    EXPECT_SIGN(::strcasecmp("HELLO", "hello"),
                sd::strcasecmp("HELLO", "hello"));
    EXPECT_SIGN(::strcasecmp("HeLlO", "HeL"), sd::strcasecmp("HeLlO", "HeL"));
    EXPECT_SIGN(::strcasecmp("hEl", "hElLo"), sd::strcasecmp("hEl", "hElLo"));
}

TEST(cmpTest, strcasecmp3) {
    const char s1[] = "\x01\xFF\x21\xDF";
    const char s2[] = "\x21\xDF\x01\xFF";
    EXPECT_SIGN(::strcasecmp(s1, s2), sd::strcasecmp(s1, s2));
    EXPECT_SIGN(::strcasecmp(s1, s1), sd::strcasecmp(s1, s1));
    EXPECT_SIGN(::strcasecmp(s2, s2), sd::strcasecmp(s2, s2));
    EXPECT_SIGN(::strcasecmp(s2, s1), sd::strcasecmp(s2, s1));
}

TEST(cmpTest, strncasecmp1) {
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

TEST(cmpTest, strncasecmp2) {
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

TEST(cmpTest, strncasecmp3) {
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

TEST(cmpTest, strncasecmp4) {
    const char s1[] = "\x00\xFF\x00\xFF";
    const char s2[] = "\xFF\x00\xFF\x00";
    EXPECT_SIGN(::strncasecmp(s1, s2, 5), sd::strncasecmp(s1, s2, 5));
    EXPECT_SIGN(::strncasecmp(s1, s1, 5), sd::strncasecmp(s1, s1, 5));
    EXPECT_SIGN(::strncasecmp(s2, s2, 5), sd::strncasecmp(s2, s2, 5));
    EXPECT_SIGN(::strncasecmp(s2, s1, 5), sd::strncasecmp(s2, s1, 5));
}

TEST(cmpTest, memcmp1) {
    EXPECT_SIGN(::memcmp("Hello", "World", 5), sd::memcmp("Hello", "World", 5));
    EXPECT_SIGN(::memcmp("Hello", "World", 6), sd::memcmp("Hello", "World", 6));
    EXPECT_SIGN(::memcmp("Hello", "Hel", 5), sd::memcmp("Hello", "Hel", 5));
    EXPECT_SIGN(::memcmp("Wor", "World", 5), sd::memcmp("Wor", "World", 5));
    EXPECT_SIGN(::memcmp("abc", "abd", 3), sd::memcmp("abc", "abd", 3));
    EXPECT_SIGN(::memcmp("", "", 0), sd::memcmp("", "", 0));
    EXPECT_SIGN(::memcmp("", "", 1), sd::memcmp("", "", 1));
    EXPECT_SIGN(::memcmp("", "abc", 3), sd::memcmp("", "abc", 3));
    EXPECT_SIGN(::memcmp("abc", "", 3), sd::memcmp("abc", "", 3));
}

TEST(cmpTest, memcmp2) {
    EXPECT_SIGN(::memcmp("Hello", "World", 2), sd::memcmp("Hello", "World", 2));
    EXPECT_SIGN(::memcmp("Hello", "World", 1), sd::memcmp("Hello", "World", 1));
    EXPECT_SIGN(::memcmp("Hello", "Hel", 3), sd::memcmp("Hello", "Hel", 3));
    EXPECT_SIGN(::memcmp("Hello", "Hel", 4), sd::memcmp("Hello", "Hel", 4));
    EXPECT_SIGN(::memcmp("Wor", "World", 3), sd::memcmp("Wor", "World", 3));
    EXPECT_SIGN(::memcmp("Wor", "World", 4), sd::memcmp("Wor", "World", 4));
    EXPECT_SIGN(::memcmp("abc", "abd", 2), sd::memcmp("abc", "abd", 2));
    EXPECT_SIGN(::memcmp("", "abc", 0), sd::memcmp("", "abc", 0));
}

TEST(cmpTest, memcmp3) {
    const char s1[] = "\x00\xFF\x00\xFF";
    const char s2[] = "\xFF\x00\xFF\x00";
    EXPECT_SIGN(::memcmp(s1, s2, 5), sd::memcmp(s1, s2, 5));
    EXPECT_SIGN(::memcmp(s1, s1, 5), sd::memcmp(s1, s1, 5));
    EXPECT_SIGN(::memcmp(s2, s2, 5), sd::memcmp(s2, s2, 5));
    EXPECT_SIGN(::memcmp(s2, s1, 5), sd::memcmp(s2, s1, 5));
}

#undef EXPECT_SIGN
