#include "gtest/gtest.h"
#include "Tests/simulations.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    simulatePhase3();

    return RUN_ALL_TESTS();
}