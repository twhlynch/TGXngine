#pragma once

#include <gtest/gtest.h>
#include "Utils.hpp"

TEST(Utils, RoundGridDown)
{
	// int basic
	EXPECT_EQ(RoundGridDown(10), 10);
	// int with offset
	EXPECT_EQ(RoundGridDown(10, 2), 12);
	// int with scale
	EXPECT_EQ(RoundGridDown(10, 0, 2), 5);
	// int with offset + scale
	EXPECT_EQ(RoundGridDown(10, 2, 2), 6);
	// float basic (truncate)
	EXPECT_EQ(RoundGridDown(10.9f), 10);
	// float with offset
	EXPECT_EQ(RoundGridDown(10.9f, 2), 12);
	// float with scale
	EXPECT_EQ(RoundGridDown(10.9f, 0, 2), 5);
	// float with offset + scale
	EXPECT_EQ(RoundGridDown(10.9f, 2, 2), 6);
	// negative int
	EXPECT_EQ(RoundGridDown(-10, 0, 2), -5);
}

TEST(Utils, IsNumber)
{
	// basic number
	EXPECT_TRUE(IsNumber("123"));
	// single digit
	EXPECT_TRUE(IsNumber("0"));
	// leading zeros
	EXPECT_TRUE(IsNumber("00123"));
	// empty string
	EXPECT_TRUE(IsNumber(""));
	// negative number
	EXPECT_FALSE(IsNumber("-123"));
	// decimal number
	EXPECT_FALSE(IsNumber("12.3"));
	// alpha characters
	EXPECT_FALSE(IsNumber("abc"));
	// alphanumeric
	EXPECT_FALSE(IsNumber("123abc"));
	// whitespace
	EXPECT_FALSE(IsNumber(" 123"));
	// symbols
	EXPECT_FALSE(IsNumber("123!"));
}
