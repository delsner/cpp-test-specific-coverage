#include <gtest/gtest.h>
#include "cov_listener.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.
    // googletest takes the ownership.
    listeners.Append(new CoverageEventListener());
    return RUN_ALL_TESTS();
}