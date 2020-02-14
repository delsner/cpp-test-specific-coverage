//
// Created by Daniel Elsner on 13.02.20.
//

#include "cov_listener.h"
#include "boost/filesystem.hpp"

// add function from gcov
extern "C" void __gcov_flush();

auto get_all_directories(const boost::filesystem::path &dir_path) {
    std::vector<std::string> directories{};
    if (exists(dir_path)) {
        boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end
        for (boost::filesystem::directory_iterator itr(dir_path); itr != end_itr; ++itr) {
            if (is_directory(itr->status())) {
                directories.emplace_back(itr->path().c_str());
            }
        }
    }
    return directories;
}

bool create_directory_recursively(const std::string &path) {
    // should be changed to c++17 std::filesystem impl
    return boost::filesystem::create_directories(path);
}

CoverageEventListener::CoverageEventListener(const std::string &coverageBaseDir, const std::string &gcnoDir) {
    this->coverageBaseDir = coverageBaseDir;
    this->gcnoDir = gcnoDir;
    this->testRunDir = std::string(coverageBaseDir) + boost::filesystem::path::preferred_separator +
                       std::to_string(GetTestProgramRunCounter());
    this->CollectGcnoFiles();
}

void CoverageEventListener::OnTestProgramStart(const testing::UnitTest &test) {
    printf("*** STARTING TEST PROGRAM ***\n");
}

void CoverageEventListener::OnTestStart(const testing::TestInfo &test_info) {
    printf("*** Test %s.%s starting.\n",
           test_info.test_suite_name(), test_info.name());
}

void CoverageEventListener::OnTestEnd(const testing::TestInfo &test_info) {
    std::string full_test_name = (std::string(test_info.test_suite_name()) + "_" + test_info.name());
    WriteCoverage(full_test_name);
    printf("*** Test %s ending ***\n", full_test_name.c_str());
}

void CoverageEventListener::OnTestProgramEnd(const testing::UnitTest &test) {
    printf("*** COMPLETELY DONE ***\n");
}

int CoverageEventListener::GetTestProgramRunCounter() const {
    auto vec = get_all_directories(this->coverageBaseDir);
    return static_cast<int>(vec.size() + 1);
}

void CoverageEventListener::CollectGcnoFiles() {
    namespace fs = ::boost::filesystem;
    if (!fs::exists(gcnoDir) || !fs::is_directory(gcnoDir)) return;

    fs::recursive_directory_iterator it(gcnoDir);
    fs::recursive_directory_iterator endit;

    while (it != endit) {
        if (fs::is_regular_file(*it) && it->path().extension() == ".gcno") {
            gcnoFiles.emplace_back(it->path().filename().c_str());
        }
        ++it;
    }
}

void CoverageEventListener::WriteCoverage(const std::string &test_name) {
    // 1. create outdir string
    std::string total_dir(testRunDir + boost::filesystem::path::preferred_separator + test_name);
    const char *coverage_out_dir = total_dir.c_str();

    // 2. create new directory for coverage for test case
    if (!create_directory_recursively(coverage_out_dir)) {
        printf("Error while creating directories\n");
    }

    // 3. get path depth of gcno directory
    std::string cwd = std::string(gcnoDir);
    size_t n = std::count(cwd.begin(), cwd.end(), boost::filesystem::path::preferred_separator);
    const char *path_depth = std::to_string(n).c_str();

    // 4. define gcov specific env variables
    setenv("GCOV_PREFIX", coverage_out_dir, true);
    setenv("GCOV_PREFIX_STRIP", path_depth, true);

    // 5. dump coverage
    printf("--- DUMPING COVERAGE FOR TEST CASE %s ---\n", test_name.c_str());
    __gcov_flush();

    // 6. copy gcno files to coverage directory
    for (auto &gcnoFile : gcnoFiles) {
        std::string from = gcnoDir + boost::filesystem::path::preferred_separator + gcnoFile;
        std::string to = total_dir + boost::filesystem::path::preferred_separator + gcnoFile;
        boost::filesystem::copy_file(from,
                                     to);
    }
}



