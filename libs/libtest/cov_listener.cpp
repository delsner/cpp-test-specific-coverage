//
// Created by Daniel Elsner on 13.02.20.
//

#include "cov_listener.h"
#include <Windows.h>

void CoverageEventListener::OnTestProgramStart(const testing::UnitTest &test) {
    printf("*** STARTING TEST PROGRAM ***\n");
    // trigger coverage dump (for clean start)
    OutputDebugString("TEST_PROGRAM_START");
}

void CoverageEventListener::OnTestStart(const testing::TestInfo &test_info) {
    std::string full_test_name = (std::string(test_info.test_suite_name()) + "_" + test_info.name());
    printf("*** Test %s starting ***\n", full_test_name.c_str());
    // trigger coverage dump (for clean first test)
    if (counter == 0)
        OutputDebugString("BEFORE_FIRST_TEST");
    counter += 1;
}

void CoverageEventListener::OnTestEnd(const testing::TestInfo &test_info) {
    std::string full_test_name = (std::string(test_info.test_suite_name()) + "_" + test_info.name());
    printf("*** Test %s ending ***\n", full_test_name.c_str());
    // trigger coverage dump after each test case for test-specific coverage
    OutputDebugString(full_test_name.c_str());
}

void CoverageEventListener::OnTestProgramEnd(const testing::UnitTest &test) {
    printf("*** COMPLETELY DONE ***\n");
    // trigger coverage dump (to see cleanup)
    OutputDebugString("TEST_PROGRAM_END");
}




