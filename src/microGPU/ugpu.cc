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
    maxCycles = 100; // Default max cycles for simulation
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

        // Set up a simple instruction for the warp ( ADD R0, R1, R2)
        warp.setCurrentInstruction(Instruction(ADD, 0, 1, 2)); // R0 = R1 + R2
        // Initialize warp state
        warp.setPipelineStage(PipelineStage::NOT_STARTED);
        // Set PC and active mask for the warp
        warp.setPc(0);
        warp.setActiveMask(std::bitset<WARP_THREAD_COUNT>().set()); // All threads active

        // Add the warp to the global collection
        addWarpToGlobalCollection(warp);
    }
    // Adding one more warp with branch instruction to test divergence handling
    Warp divergentWarp(5, ThreadGroup(), READY, NOT_STARTED, true);
    divergentWarp.setCurrentInstruction(Instruction(InstructionType::BRANCH, 0, 1, 2));
    addWarpToGlobalCollection(divergentWarp);
    std::cout << "(microGPU) Branch warp with ID " << divergentWarp.getId() << " added to global collection." << std::endl;
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
    std::cout << "(microGPU) Assigned Warp ID " << warp.getId() << " to ComputeUnit ID " << smId << std::endl;
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

void MicroGPU::performWarpSchedulingSimple() {
    // Simple scheduling: Assign all warps to the first two compute unit (for testing)
    int smId = 0; // Assign to first ComputeUnit for simplicity
    for (const auto &warp : globalWarpCollection) {
        assignWarpToSM(smId, warp);
        smId = (smId + 1) % 2; // Move to next ComputeUnit in round-robin fashion
    }
    // Clear global collection after assignment
    globalWarpCollection.clear();
    std::cout << "(microGPU) Simple warp scheduling completed." << std::endl;
}

void MicroGPU::executeComputeUnits() {
    for (auto &cu : computeUnit) {
        cu.execute();
    }
}

void MicroGPU::executeGPU(){
    int cycleCount = 0;
    for (int cycle = 0; cycle < maxCycles; ++cycle) {
        std::cout << "\n--- Simulation Cycle: " << cycle << " ---\n";
        // Execute warps in compute units for one cycle
        executeComputeUnits();
        cycleCount = cycle; 

        // Check if all warps have completed execution
        if (allWarpsCompleted()) {
            std::cout << "(system) All warps have completed execution. Ending simulation at cycle:  " << cycle << std::endl;
            break;
        }
    }

    std :: cout << "(microGPU) GPU executed for cycles: " << cycleCount + 1 << std::endl;
}