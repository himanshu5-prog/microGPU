 # microGPU

[![Documentation](https://img.shields.io/badge/docs-doxygen-blue)](https://himanshu5-prog.github.io/microGPU/)
 [![Build and Deploy Doxygen Docs](https://github.com/himanshu5-prog/microGPU/actions/workflows/doxygen.yml/badge.svg)](https://github.com/himanshu5-prog/microGPU/actions/workflows/doxygen.yml)
 ![GitHub top language](https://img.shields.io/github/languages/top/himanshu5-prog/microGPU)
 [![GitHub issues](https://img.shields.io/github/issues/himanshu5-prog/microGPU)](https://github.com/himanshu5-prog/microGPU/issues)
 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

 I am creating a simple functional model of GPU to understand its architecture. I have started with class definition of thread and warp and later added compute units.

 Currently, microGPU is able to accept warps in global collection and then schedule to computeUnits. 

 I will be adding more functionality and update this README.

Current status (02/08) :
The test is able to create warp and assign to Compute Units. Compute unit is able to execute warp in round robin manner. It has been verified from log file by looking at the pipeline stage with time.


Compiling the code

1. Compile in debug mode

    make

2. Compile in release mode

    make BUILD=release

3. Sanitizer mode on

    make SAN=1
