//
// Created by Daniel Elsner on 12.02.20.
//

#include <foo.h>
#include "testfoo.h"

using ::testing::Return;

FooTest::FooTest() {
    // Have qux return true by default
    ON_CALL(m_bar, qux()).WillByDefault(Return(true));
    // Have norf return false by default
    ON_CALL(m_bar, norf()).WillByDefault(Return(false));
}

// FooTest::~FooTest() {}; // same as below
FooTest::~FooTest() = default;

void FooTest::SetUp() {};

void FooTest::TearDown() {};

// tests with fixtures
TEST_F(FooTest, ByDefaultBazTrueIsTrue) {
    Foo foo(m_bar);
    EXPECT_EQ(foo.baz(true), true);
}

TEST_F(FooTest, ByDefaultBazFalseIsFalse) {
    Foo foo(m_bar);
    EXPECT_EQ(foo.baz(false), false);
}

TEST_F(FooTest, SometimesBazFalseIsTrue) {
    Foo foo(m_bar);
    // Have norf return true for once
    EXPECT_CALL(m_bar, norf()).WillOnce(Return(true));
    EXPECT_EQ(foo.baz(false), true);
}

// simple test
TEST(FooTestSuite, AlwaysTrue) {
    ASSERT_EQ(true, true);
}