#include "ugpu.hh"

MicroGPU::MicroGPU() {
    std::cout << "MicroGPU initialized with " << SM_COUNT << " SMs." << std::endl;
}

void MicroGPU::init() {
    // Initialize each SM
    for (int i = 0; i < SM_COUNT; ++i) {
        computeUnit[i].setSmId(i);
        computeUnit[i].setState(IDLE);
        computeUnit[i].printId();
    }
    std::cout << "MicroGPU SMs initialized." << std::endl;
}