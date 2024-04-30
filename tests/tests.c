#include <stdio.h>
#include "tests.h"




int RunTests(void)
{
    const TestFunction tests[] = {
        Test_HexAdd,
        Test_HexSubtract,
        Test_HexDistanceFromOrigin,
        Test_HexDistance,
        Test_HexDirection,
        Test_HexLine,

        Test_HexSerDe,
    };

    int failures = 0;

    int test_count = sizeof(tests) / sizeof(tests[0]);
    printf("Running %d tests\n", test_count);
    for (int i = 0; i < test_count; i++) {
        int failed_assertions = tests[i]();
        if (failed_assertions > 0) {
            printf(ANSI_COLOR_RED "Test %d failed %d assertions\n" ANSI_COLOR_RESET, i, failed_assertions);
            failures += failed_assertions;
        }
    }

    if (failures == 0) {
        printf(ANSI_COLOR_GREEN "All tests passed!\n" ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_RED "%d tests failed\n" ANSI_COLOR_RESET, failures);
    }

    return 0;
}


int main(void)
{
    RunTests();
}

