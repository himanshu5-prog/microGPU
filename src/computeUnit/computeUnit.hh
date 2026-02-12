#ifndef COMPUTEUNIT_HH
#define COMPUTEUNIT_HH

#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>
#include<cassert>

#include "../warp/warp.hh"

enum SMState {
    IDLE,
    BUSY,
    ERROR
};


class ComputeUnit {
    std::vector<Warp> warps;

    // Each compute unit has its own ID
    int smId;

    // Warp ID which will be executed in next cycle
    int nextWarpId;

    // Current warp ID being executed
    size_t currentWarpId;

    // Current cycle
    int currentCycle;

    // State of the compute unit
    SMState state;

    public:
        ComputeUnit() : nextWarpId(0), currentWarpId(0), currentCycle(0), state(SMState::IDLE) {}
       
        // Setter methods
        void setState(SMState newState);
        void setCurrentWarpId(int warpId);
        void setWarp(const Warp &warp);
        void setSmId(int id) { smId = id; }

        // Increment cycle count for the compute unit
        void incrementCycle() { currentCycle++; }

        // Execute the current warp and advance its pipeline stage
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

        // Method to calculate the next warp ID to execute based on round-robin scheduling
        void calculateNextWarpId();
        
};

#endif // COMPUTEUNIT_HH