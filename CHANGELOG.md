# Changelog

All notable changes to this project will be documented in this file.

The format is based on
[Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project
adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [2.0.0] - 2023-08-01

## Added

-   Assert null and assert same failure message contains the pointer reference.
-   A suite can have an optional set up and tear down function.

## Changed

-   Combine functions `get_failure_count` and `clear_tests` in function
    `run_tests`.

## [1.0.1] - 2023-07-31

### Fixed

-   In assertion messages, the variable name was displayed instead of the
    variable value.
-   Fix messages of negated assertions.

## [1.0.0] - 2023-07-31

### Added

-   Create a test suite with test cases.
-   Create a test case as function.
-   Check assertions with ASSERT macros.
-   Run tests with CI friendly output on console and return value.

[unreleased]: https://github.com/falkoschumann/cunit/compare/v2.0.0...HEAD
[2.0.0]: https://github.com/falkoschumann/cunit/compare/v1.0.1...v2.0.0
[1.0.1]: https://github.com/falkoschumann/cunit/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/falkoschumann/cunit/releases/tag/v1.0.0
