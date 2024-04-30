#ifndef HEX__TESTS_H
#define HEX__TESTS_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef int (*TestFunction)(void);

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf(ANSI_COLOR_RED "Test Failed: %s\n" ANSI_COLOR_RESET, message); \
            return 1; \
        } \
    } while (0)

// Add names of Test functions here
int Test_HexSerDe(void);
int Test_HexAdd(void);
int Test_HexSubtract(void);
int Test_HexLine(void);
int Test_HexDistanceFromOrigin(void);
int Test_HexDistance(void);
int Test_HexDirection(void);

#endif // HEX__TESTS_H

