#ifndef COMPUTEUNIT_HH
#define COMPUTEUNIT_HH

#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>

#include "../warp/warp.hh"

enum SMState {
    IDLE,
    BUSY,
    ERROR
};


class ComputeUnit {
    std::vector<Warp> warps;
    int smId;
    int nextWarpId;
    int currentWarpId;
    int currentCycle;
    SMState state;

    public:
        ComputeUnit() : nextWarpId(0), currentWarpId(-1), currentCycle(0), state(SMState::IDLE) {}
        
        void setState(SMState newState);
        void setCurrentWarpId(int warpId);
        void setWarp(const Warp &warp);
        void setSmId(int id) { smId = id; }
        void incrementCycle() { currentCycle++; }
        void execute(); 
        // Getter methods
        int getCurrentWarpId();
        SMState getState() const;
        int getNextWarpId();
        int getWarpCollectionSize() const;
        int getCurrentCycle() const { return currentCycle; }
        int getSmId() const { return smId; }

        // Print method for debugging
        void printId() const { std::cout << "(ComputeUnit) ComputeUnit ID: " << smId << std::endl; }
        
};

#endif // COMPUTEUNIT_HH