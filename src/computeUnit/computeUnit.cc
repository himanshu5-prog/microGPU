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
