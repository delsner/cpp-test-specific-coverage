#ifndef CPPCOVERAGE_COV_LISTENER_H
#define CPPCOVERAGE_COV_LISTENER_H

#include <gtest/gtest.h>

class CoverageEventListener : public testing::EmptyTestEventListener {
public:
    CoverageEventListener() = default;

    void OnTestProgramStart(const testing::UnitTest &test) override;

    void OnTestStart(const testing::TestInfo &test_info) override;

    void OnTestEnd(const testing::TestInfo &test_info) override;

    void OnTestProgramEnd(const testing::UnitTest &test) override;
private:
    int counter = 0;
};

#endif //CPPCOVERAGE_COV_LISTENER_H
