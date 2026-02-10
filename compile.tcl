## Deprecated. Use make command instead. This file will not be updated. 
## Please refer to Makefile for compilation instructions.
g++ -std=c++17 -Wall -g -O0 -Wextra -pedantic \
src/*.cc \
src/computeUnit/*.cc \
src/warp/*.cc \
src/microGPU/*.cc \
src/thread/*.cc \
-o microGPU