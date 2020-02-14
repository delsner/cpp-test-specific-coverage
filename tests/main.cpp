#include <gtest/gtest.h>
#include "cov_listener.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.
    // googletest takes the ownership.
    listeners.Append(new CoverageEventListener("/Users/delsner/Downloads/runs",
                                               "/Users/delsner/workspace/00_TUM/cppcoverage/cmake-build-debug/tests/CMakeFiles/unittests.dir"));
    return RUN_ALL_TESTS();
}