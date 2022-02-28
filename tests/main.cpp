#include <gtest/gtest.h>

#ifdef TEST_LISTENER
#include "cov_listener.h"
#endif


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
#ifdef TEST_LISTENER
    // Gets hold of the event listener list.
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.
    // googletest takes the ownership.
    listeners.Append(new CoverageEventListener());
#endif
    return RUN_ALL_TESTS();
}