#pragma once

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "StringUtils.hpp"

// NOTE: StringSplit and LastStringSplit dont include an empty string when there is a trailing delimiter

#define list std::vector<std::string>

TEST(StringUtils, StringSplit)
{
	// basic
	EXPECT_EQ(StringSplit("a b", " "), list({"a", "b"}));
	// multiple spaces
	EXPECT_EQ(StringSplit("a  b", " "), list({"a", "", "b"}));
	// multiple spaces as delim
	EXPECT_EQ(StringSplit("a  b", " +"), list({"a", "b"}));
	// basic multiple
	EXPECT_EQ(StringSplit("a,b,c", ","), list({"a", "b", "c"}));
	// trailing delim
	EXPECT_EQ(StringSplit("a,b,", ","), list({"a", "b"}));
	// leading delim
	EXPECT_EQ(StringSplit(",a,b", ","), list({"", "a", "b"}));
	// empty string
	EXPECT_EQ(StringSplit("", ","), list({""}));
	// no delim
	EXPECT_EQ(StringSplit("abc", ","), list({"abc"}));
	// multiple delims
	EXPECT_EQ(StringSplit("a,b;c.d", "[,;\\.]"), list({"a", "b", "c", "d"}));
}

#undef list

TEST(StringUtils, LastStringSplit)
{
	// basic
	EXPECT_EQ(LastStringSplit("a b", " "), "b");
	// multiple spaces
	EXPECT_EQ(LastStringSplit("a  b", " "), "b");
	// multiple spaces as delim
	EXPECT_EQ(LastStringSplit("a  b", " +"), "b");
	// basic multiple
	EXPECT_EQ(LastStringSplit("a,b,c", ","), "c");
	// trailing delim
	EXPECT_EQ(LastStringSplit("a,b,", ","), "b");
	// leading delim
	EXPECT_EQ(LastStringSplit(",a,b", ","), "b");
	// empty string
	EXPECT_EQ(LastStringSplit("", ","), "");
	// no delim
	EXPECT_EQ(LastStringSplit("abc", ","), "abc");
	// multiple delims
	EXPECT_EQ(LastStringSplit("a,b;c.d", "[,;\\.]"), "d");
}

TEST(StringUtils, ToString)
{
	// literal int
	EXPECT_EQ(ToString(1), "1");
	// literal float
	EXPECT_EQ(ToString(1.0f), "1.000000");
	// literal float
	EXPECT_EQ(ToString(1.0), "1.000000");
	// size_t
	EXPECT_EQ(ToString(static_cast<size_t>(1)), "1");
	// literal string
	EXPECT_EQ(ToString("1"), "1");
	// std string
	EXPECT_EQ(ToString(std::string("1")), "1");
	// literal char
	EXPECT_EQ(ToString('1'), "1");
	// literal bool
	EXPECT_EQ(ToString(true), "true");
}

TEST(StringUtils, StringConcat)
{
	// string with int
	EXPECT_EQ(StringConcat("hello", 123), "hello123");
	// string with string
	EXPECT_EQ(StringConcat("hello", std::string(" world")), "hello world");
	// string with char*
	EXPECT_EQ(StringConcat("hello", " world"), "hello world");
	// empty string with int
	EXPECT_EQ(StringConcat("", 42), "42");
	// empty string with string
	EXPECT_EQ(StringConcat("", std::string("test")), "test");
	// empty string with char*
	EXPECT_EQ(StringConcat("", "test"), "test");
	// string with zero
	EXPECT_EQ(StringConcat("number: ", 0), "number: 0");
	// string with negative int
	EXPECT_EQ(StringConcat("value: ", -10), "value: -10");
	// string with float
	EXPECT_EQ(StringConcat("value: ", 3.14), "value: 3.140000");
	// string with bool
	EXPECT_EQ(StringConcat("value: ", true), "value: true");
	// multiple values
	EXPECT_EQ(StringConcat("1", 1, 1.0, '1', true), "111.0000001true");
}

#define Expect_StringReplaceAll(input, from, to, expected) \
	str = input;                                           \
	StringReplaceAll(str, from, to);                       \
	EXPECT_EQ(str, expected);

TEST(StringUtils, StringReplaceAll)
{
	std::string str;

	// single occurrence
	Expect_StringReplaceAll("ab", "b", "c", "ac");
	// multiple occurrences
	Expect_StringReplaceAll("aba", "a", "c", "cbc");
	// substring not found
	Expect_StringReplaceAll("abc", "x", "y", "abc");
	// empty string
	Expect_StringReplaceAll("abc", "", "y", "abc");
	// remove
	Expect_StringReplaceAll("aaa", "a", "", "");
	// overlapping patterns
	Expect_StringReplaceAll("aaaa", "aa", "b", "bb");
	// same string
	Expect_StringReplaceAll("hello", "hello", "hello", "hello");
	// start of string
	Expect_StringReplaceAll("abcabc", "abc", "x", "xx");
	// end of string
	Expect_StringReplaceAll("123abc", "abc", "xyz", "123xyz");
	// empty input
	Expect_StringReplaceAll("", "a", "b", "");
}

#undef Expect_StringReplaceAll
