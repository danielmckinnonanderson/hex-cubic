#!/usr/bin/env sh

# Compile the test file
gcc ./hex.c ./tests/test_serde.c ./tests/tests.c ./tests/test_hex.c -o ./tests/bin/test

