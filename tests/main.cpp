#include <gtest/gtest.h>
#include "listener.h"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    ::testing::TestEventListeners &listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.  googletest takes the ownership.
    listeners.Append(new MinimalistPrinter);
    return RUN_ALL_TESTS();
}