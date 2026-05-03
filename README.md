LibCSS -- a CSS parser and selection engine
===========================================

Upstream and credits
--------------------

LibCSS is developed by the **NetSurf** project. This repository is derived
from that upstream work; copyright and license notices in individual source
files remain in force (see file headers, typically MIT).

Original project and history:

* Upstream repository: [https://git.netsurf-browser.org/libcss.git](https://git.netsurf-browser.org/libcss.git)
* NetSurf browser: [https://www.netsurf-browser.org/](https://www.netsurf-browser.org/)

About this patched tree
------------------------

This checkout includes **CMake** build support and **Microsoft Visual C++**
(MSVC) compatibility fixes that are not part of the upstream Makefile-focused
workflow. Summary of portability changes:

* `CMakeLists.txt` — configures `css` and test targets; vendored dependencies
  live under `external/` (see `.gitmodules`).
* Windows / MSVC — `restrict` mapping interacts badly with C99
  `array[restrict N]` parameters; bloom merge uses pointer parameters instead.
* MSVC — zero-initialisation of the `css_fixed_or_calc` union uses C99
  compound literals instead of invalid casts from integer.

On Windows, after initializing submodules and installing a Ninja + MSVC
environment, you can build from the repo root with `build.ps1` (loads
`vcvars64`, then `cmake --build _build`). A plain `cmake -S . -G Ninja -B
_build` followed by `cmake --build _build` is equivalent once the toolchain
environment is set.

The sections below describe the **original** upstream build and workflow
(`make`, pkg-config, Perl tests) and still apply if you use that layout.

Overview
--------

LibCSS is a CSS parser and selection engine. It aims to parse the forward
compatible CSS grammar.

Requirements
------------

LibCSS requires the following tools:

* A C99 capable C compiler
* GNU make or compatible
* Pkg-config
* Perl (for the testcases)
* Python3 (minimum 3.6, for generated selection code)

LibCSS also requires the following libraries to be installed:

* LibParserUtils
* LibWapcaplet

Compilation
-----------

If necessary, modify the toolchain settings in the Makefile.
Invoke make:

    make

Regenerating generated selection source code
--------------------------------------------

To regenerate the selection sources (computed style data accesses),
note this requires python3:

    make select_generator

Verification
------------

To verify that the parser is working, it is necessary to specify a
different makefile target than that used for normal compilation, thus:

    make test

API documentation
-------------------

Currently, there is none. However, the code is well commented and the
public API may be found in the "include" directory. The testcase sources
may also be of use in working out how to use it.
