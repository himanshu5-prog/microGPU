#include "ugpu.hh"

MicroGPU::MicroGPU() {
    std::cout << "(microGPU) MicroGPU initialized with " << SM_COUNT << " SMs." << std::endl;
}

void MicroGPU::init() {
    // Initialize each SM
    for (int i = 0; i < SM_COUNT; ++i) {
        computeUnit[i].setSmId(i);
        computeUnit[i].setState(IDLE);
        computeUnit[i].printId();
    }
    std::cout << "(microGPU) MicroGPU SMs initialized." << std::endl;
}

void MicroGPU::addWarpToGlobalCollection(const Warp &warp) {
    globalWarpCollection.push_back(warp);
    std::cout << "(microGPU) Warp with ID " << warp.getId() << " added to global collection." << std::endl;
}

int MicroGPU::getGlobalWarpCollectionSize() const {
    return globalWarpCollection.size();
}

void MicroGPU::createGlobalWarpCollectionTest() {
    // Create some test warps and add them to the global collection
    for (int i = 0; i < 5; ++i) {
        ThreadGroup threadGroup;
        for (int t = 0; t < WARP_THREAD_COUNT; ++t) {
            threadGroup[t] = Thread(i * WARP_THREAD_COUNT + t, ACTIVE);
        }
        Warp warp(i, threadGroup);
        addWarpToGlobalCollection(warp);
    }
    std::cout << "(microGPU) Total warps in global collection: " << getGlobalWarpCollectionSize() << std::endl;
}

void MicroGPU::performWarpScheduling() {
    // Simple round-robin scheduling of warps to SMs
    int smIndex = 0;
    for (const auto &warp : globalWarpCollection) {
        assignWarpToSM(smIndex, warp);
        smIndex = (smIndex + 1) % SM_COUNT;
    }
}

void MicroGPU::assignWarpToSM(int smId, const Warp &warp) {
    computeUnit[smId].setWarp(warp);
    std::cout << "(microGPU) Assigned Warp ID " << warp.getId() << " to SM ID " << smId << std::endl;
}

void MicroGPU::printComputeUnitStatus() const {
    for (const auto &sm : computeUnit) {
        sm.printId();
        std::cout << "  State: " << (sm.getState() == IDLE ? "IDLE" : sm.getState() == BUSY ? "BUSY" : "ERROR") << std::endl;
        std::cout << "  Warps assigned: " << sm.getWarpCollectionSize() << std::endl;
    }
}