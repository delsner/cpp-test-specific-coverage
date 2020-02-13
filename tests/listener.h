//
// Created by Daniel Elsner on 13.02.20.
//

#ifndef CPPCOVERAGE_LISTENER_H
#define CPPCOVERAGE_LISTENER_H

#include <gtest/gtest.h>

class MinimalistPrinter : public testing::EmptyTestEventListener {
    // Called before a test starts.
    virtual void OnTestStart(const testing::TestInfo &test_info) {
        printf("*** Test %s.%s starting.\n",
               test_info.test_suite_name(), test_info.name());
    }

    // Called after a test ends.
    virtual void OnTestEnd(const testing::TestInfo &test_info) {
        printf("*** Test %s.%s ending.\n",
               test_info.test_suite_name(), test_info.name());
    }
};

#endif //CPPCOVERAGE_LISTENER_H
