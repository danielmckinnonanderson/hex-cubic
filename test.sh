#!/usr/bin/env bash

# Compile the test file
gcc ./hex.c ./tests/test_serde.c ./tests/tests.c -o ./tests/bin/test

