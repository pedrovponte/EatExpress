#include "gtest/gtest.h"
#include "Tests/simulations.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    simulateDijkstraPhase2();

    return RUN_ALL_TESTS();
}