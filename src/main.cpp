#include <fstream>
#include "gtest/gtest.h"
#include "src/app/app.h"

using namespace std;

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    chooseMap();

    cout << endl << "\t(X) Exit ";
    getchar();
    return 0;
    //return RUN_ALL_TESTS();
}