 # microGPU

[![Documentation](https://img.shields.io/badge/docs-doxygen-blue)](https://himanshu5-prog.github.io/microGPU/)
 [![Build and Deploy Doxygen Docs](https://github.com/himanshu5-prog/microGPU/actions/workflows/doxygen.yml/badge.svg)](https://github.com/himanshu5-prog/microGPU/actions/workflows/doxygen.yml)
 [![Compile Check](https://github.com/himanshu5-prog/microGPU/actions/workflows/compileCheck.yml/badge.svg)](https://github.com/himanshu5-prog/microGPU/actions/workflows/compileCheck.yml)
 [![GitHub issues](https://img.shields.io/github/issues/himanshu5-prog/microGPU)](https://github.com/himanshu5-prog/microGPU/issues)
 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

microGPU is a small C++ project that implements a functional model of a GPU to explore and understand GPU architecture. The repository defines classes for threads and warps and builds up to compute units and a scheduler; the README includes badges linking to documentation, CI status, issue tracker, and license.

Current functionality: the project accepts warps into a global collection and schedules them onto compute units, which execute warps in a round-robin fashion. Tests verify that warps are created, assigned, and progressed through pipeline stages; logs record pipeline stage changes with timestamps to validate behavior.

I have added logic to handle simple case of divergence as well.

Compiling the code

1. Compile in debug mode

    make

2. Compile in release mode

    make BUILD=release

3. Sanitizer mode on
s
    make SAN=1

## Documentation

Built API docs (Doxygen): [HTML documentation](https://himanshu5-prog.github.io/microGPU/index.html)
