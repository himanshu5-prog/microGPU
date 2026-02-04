#include "ugpu.hh"

MicroGPU::MicroGPU() {
    currentCycle = 0;
    std::cout << "(microGPU) MicroGPU initialized with " << CU_COUNT << " SMs." << std::endl;
}

void MicroGPU::init() {
    // Initialize each SM
    for (int i = 0; i < CU_COUNT; ++i) {
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
    // Currently a simple implementation - All warps are assigned to compute units in round-robin fashion in single cycle
    // Simple round-robin scheduling of warps to SMs
    int smIndex = 0;
    for (const auto &warp : globalWarpCollection) {
        assignWarpToSM(smIndex, warp);
        smIndex = (smIndex + 1) % CU_COUNT;
    }
    // Clear global collection after assignment
    globalWarpCollection.clear();
    std::cout << "(microGPU) Warp scheduling completed." << std::endl;
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

// Check if all compute units are done processing their warps
bool MicroGPU::allComputeUnitsDone() const {
    for (const auto &cu : computeUnit) {
        if (cu.getWarpCollectionSize() > 0) {
            return false;
        }
    }
    return true;
}

bool MicroGPU::allWarpsCompleted() const {
    if (globalWarpCollection.empty() && allComputeUnitsDone()) {
        // No warp pending in global collection and all compute units are done processing warps to completion
        return true;
    }
    return false;
}