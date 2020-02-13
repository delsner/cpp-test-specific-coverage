//
// Created by Daniel Elsner on 13.02.20.
//

#ifndef CPPCOVERAGE_LISTENER_H
#define CPPCOVERAGE_LISTENER_H

#include <gtest/gtest.h>

extern "C" void __gcov_flush();

static void write_coverage(const char *test_name) {
    // 0. set base directory
    const char *base_dir = "/Users/delsner/Downloads/runs";

    // 1. create hash to identify run number
    const char *hash = "1";
    std::string total(std::string(base_dir) + "/" + hash + "/" + test_name);
    const char *path = total.c_str();

    // 2. create new directory for coverage for test case
    printf("--- CREATING DIRECTORY %s ---\n", path);
    system((std::string("mkdir -p ") + path).c_str()); // TODO: only works on unix-like OS

    // 3. get path depth of current directory
    char *working_dir_path = realpath(".", NULL);
    std::string cwd = std::string(working_dir_path);
    size_t n = std::count(cwd.begin(), cwd.end(), '/');
    std::string path_depth = std::to_string(n);

    // 4. define gcov specific env variables
    setenv("GCOV_PREFIX", path, true);
    setenv("GCOV_PREFIX_STRIP", path_depth.c_str(), true);

    // 5. dump coverage
    printf("--- DUMPING COVERAGE FOR TEST CASE %s ---\n", test_name);
    __gcov_flush();
}

class MinimalistPrinter : public testing::EmptyTestEventListener {

public:
    void OnTestProgramStart(const testing::UnitTest &test) override {
        printf("*** STARTING TEST PROGRAM ***\n");
    }

    void OnTestStart(const testing::TestInfo &test_info) override {
        printf("*** Test %s.%s starting.\n",
               test_info.test_suite_name(), test_info.name());
    }

    void OnTestEnd(const testing::TestInfo &test_info) override {
        std::string full_test_name = (std::string(test_info.test_suite_name()) + "_" + test_info.name());
        char test_name[full_test_name.size() + 1]; // add null char
        strncpy(test_name, full_test_name.c_str(), sizeof(test_name));
        write_coverage(test_name);
        printf("*** Test %s.%s ending.\n",
               test_info.test_suite_name(), test_info.name());
    }

    void OnTestProgramEnd(const testing::UnitTest &test) override {
        printf("*** COMPLETELY DONE ***\n");
    }

};

#endif //CPPCOVERAGE_LISTENER_H
