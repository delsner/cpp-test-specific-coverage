# Test-specific Code Coverage in C++ with OpenCppCoverage

This repository demonstrates the use of OpenCppCoverage to gather coverage per test case in C++ projects using Google's Testing framework.

## Google Test

[Google Test](https://github.com/google/googletest) is Google's C++ test framework used to create test cases.
The [hooks inside Google Test](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#defining-event-listeners) can be used for implementing the necessary control flow to realize coverage per test case.

## OpenCppCoverage

[`OpenCppCoverage`](https://github.com/OpenCppCoverage/OpenCppCoverage) is an open-source tool for obtaining coverage from `.pdb` files as created by MS Visual C++.

It is modified for test-specific coverage in [this fork](https://github.com/delsner/OpenCppCoverage).

## Setup

1. Download binary of [fork from OpenCppCoverage](https://github.com/delsner/OpenCppCoverage) and add to `$PATH`
2. Clone this repository and build it with `cmake` (you can use the internal version of VS)
3. Make sure you can run `unittests.exe (tests\unittests.exe)` with x64-Debug configuration
4. Navigate to `.\out\build\x64-Debug\tests`, make sure there is a `unittests.pdb` and `unittests.exe` file and execute OpenCppCoverage as follows:
```sh
$ opencppcoverage.exe --sources PATH_TO_REPO\libs --sources PATH_TO_REPO\tests --excluded_sources PATH_TO_REPO\tests\cov_listener* --excluded_sources PATH_TO_REPO\tests\main* --enable_debug_callback -- unittests.exe
```
