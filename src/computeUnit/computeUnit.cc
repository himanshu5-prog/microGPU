#include "computeUnit.hh"

void ComputeUnit::setState(SMState newState) {
    state = newState;
}

void ComputeUnit::setCurrentWarpId(int warpId) {
    currentWarpId = warpId;
}
void ComputeUnit::setWarp(const Warp &warp) {
    warps.push_back(warp);
}
int ComputeUnit::getCurrentWarpId() {
    return currentWarpId;
}
SMState ComputeUnit::getState() const {
    return state;
}
int ComputeUnit::getNextWarpId() {
    return nextWarpId++;
}

int ComputeUnit::getWarpCollectionSize() const {
    return warps.size();
}

void ComputeUnit::execute(){
    if (warps.empty()) {
        std::cout << "(ComputeUnit " << smId << ") No warps to execute." << std::endl;
        currentWarpId = 0;
        return;
    }
    std :: cout << "(ComputeUnit) : " << smId << " Cycle: " << currentCycle <<", id: " << warps[currentWarpId].getId() << "\n";
    assert (currentWarpId >= 0 && currentWarpId < warps.size());
    std::cout << "(ComputeUnit: " << smId << ") Executing warp ID: " << warps[currentWarpId].getId() 
              << " at pipeline stage: " << warps[currentWarpId].getPipelineStageString() << std::endl;

    // Simulate execution by advancing the pipeline stage of the current warp
    if (warps[currentWarpId].getPipelineStage() == PipelineStage::NOT_STARTED) {
        warps[currentWarpId].setPipelineStage(PipelineStage::STAGE_0);
    } else if (warps[currentWarpId].getPipelineStage() == PipelineStage::STAGE_0) {
        warps[currentWarpId].setPipelineStage(PipelineStage::STAGE_1);
    } else if (warps[currentWarpId].getPipelineStage() == PipelineStage::STAGE_1) {
        warps[currentWarpId].setPipelineStage(PipelineStage::STAGE_2);
    } else if (warps[currentWarpId].getPipelineStage() == PipelineStage::STAGE_2) {
        warps[currentWarpId].setPipelineStage(PipelineStage::STAGE_3);
    } else if (warps[currentWarpId].getPipelineStage() == PipelineStage::STAGE_3) {
        warps[currentWarpId].setPipelineStage(PipelineStage::DONE);
    } 

    std::cout << "(ComputeUnit: " << smId << ") Completed execution for warp ID: " << warps[currentWarpId].getId() 
              << " at pipeline stage: " << warps[currentWarpId].getPipelineStageString() << std::endl;
    
    currentWarpId += 1; // Move to the next warp for the next cycle

    // Iterate through all warps and remove the warps that are done
    warps.erase(std::remove_if(warps.begin(), warps.end(), [](const Warp& warp) {
        return warp.getPipelineStage() == PipelineStage::DONE;
    }), warps.end());

    if (currentWarpId >= warps.size()) {
        currentWarpId = 0; // Loop back to the first warp
    }
    currentCycle += 1; // Increment cycle count for the compute unit

}   
