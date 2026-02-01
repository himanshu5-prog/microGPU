g++ -std=c++17 -Wall -g -O0 -Wextra -pedantic \
src/*.cc \
src/computeUnit/*.cc \
src/warp/*.cc \
src/microGPU/*.cc \
-o tinyGpu