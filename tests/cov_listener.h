//
// Created by Daniel Elsner on 13.02.20.
//

#ifndef CPPCOVERAGE_COV_LISTENER_H
#define CPPCOVERAGE_COV_LISTENER_H

#include <gtest/gtest.h>

class CoverageEventListener : public testing::EmptyTestEventListener {
public:
    explicit CoverageEventListener(const std::string &coverageBaseDir, const std::string &gcnoDir);

    void OnTestProgramStart(const testing::UnitTest &test) override;

    void OnTestStart(const testing::TestInfo &test_info) override;

    void OnTestEnd(const testing::TestInfo &test_info) override;

    void OnTestProgramEnd(const testing::UnitTest &test) override;

    void WriteCoverage(const std::string& test_name);

private:
    std::string coverageBaseDir;
    std::string testRunDir;
    // path where .gcno files are located (typically same location as object files of executable)
    // generated when the source file is compiled with the GCC `-ftest-coverage` option
    std::string gcnoDir;
    // contains information to reconstruct the basic block graphs and assign source line numbers to blocks
    // https://gcc.gnu.org/onlinedocs/gcc/Gcov-Data-Files.html
    std::vector<std::string> gcnoFiles{};

    int GetTestProgramRunCounter() const; // cannot change any internals
    void CollectGcnoFiles(); // cannot change any internals
};

#endif //CPPCOVERAGE_COV_LISTENER_H
