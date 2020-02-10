# Code Coverage in C(++)

This repository aims to discover different approaches to gather coverage per test case in C(++) projects.

## Coding Standard

In this project we follow the [Abseil Live at Head philosophy](https://abseil.io/about/philosophy) as well as the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
To keep up with `absl` features, one can read the [regular tips](https://abseil.io/tips/).

## Writing Tests

### Google Test

[Google Test](https://github.com/google/googletest) is Google's C++ test framework used to create test cases.
The [hooks inside Google Test](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#defining-event-listeners) can be used for implementing the necessary control flow to realize coverage per test case.

## Coverage Tools

### Clang `llvm-cov`

The first approach will be to use `clang` for obtaining [code coverage](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html).

### OpenCppCoverage

The second approach for MS Compiler will be [`opencppcoverage`](https://github.com/OpenCppCoverage/OpenCppCoverage).

### GCC `gcov`

Finally, [`gcov`](https://gcc.gnu.org/onlinedocs/gcc/Gcov.html) is used as a third alternative.