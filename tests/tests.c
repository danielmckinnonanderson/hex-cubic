#include <stdio.h>
#include "tests.h"


const TestFunction tests[] = {
    Test_HexSerDe,
};


int RunTests(void) {
    int failures = 0;

    for (int i = 0; i < sizeof(tests) / sizeof(TestFunction); i++) {
        int failed_assertions = tests[i]();
        if (failed_assertions > 0) {
            printf(ANSI_COLOR_RED "Test %d failed %d assertions\n" ANSI_COLOR_RESET, i, failed_assertions);
            failures += failed_assertions;
        }
    }

    printf("\n");
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

