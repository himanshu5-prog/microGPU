#ifndef COMPUTEUNIT_HH
#define COMPUTEUNIT_HH

#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>
#include<cassert>
#include<algorithm>
#include "../warp/warp.hh"

enum SMState {
    IDLE,
    BUSY,
    ERROR
};

/** @class ComputeUnit
 *  @brief Represents a GPU compute unit
 *  @ingroup Architecture
 * The ComputeUnit class encapsulates the state and behavior of a GPU compute unit.
 * It executes Warp objects, which are groups of threads that execute instructions in lockstep.
 * The ComputeUnit manages the scheduling of warps and executes them in simple round-robin fashion.
 * 
 * Each warp can be in one of following pipeline stages: 
 * 
 * -> NOT_STARTED, 
 * -> STAGE_0, 
 * -> STAGE_1, 
 * -> STAGE_2, 
 * -> STAGE_3, 
 * -> DONE.
 * 
 */

class ComputeUnit {
    std::vector<Warp> warps;

    // Each compute unit has its own ID
    int smId;

    // Current warp ID being executed
    size_t currentWarpId;

    // Current cycle
    int currentCycle;

    // State of the compute unit
    SMState state;

    public:
        ComputeUnit() : currentWarpId(0), currentCycle(0), state(SMState::IDLE) {}
       
        // Setter methods
        void setState(SMState newState);
        void setCurrentWarpId(int warpId);
        void setWarp(const Warp &warp);
        void setSmId(int id) { smId = id; }

        // Increment cycle count for the compute unit
        void incrementCycle() { currentCycle++; }

        /// Execute the current warp and advance its pipeline stage. Called once per cycle.
        void execute(); 

        // Getter methods
        int getCurrentWarpId();
        SMState getState() const;
        int getWarpCollectionSize() const;
        int getCurrentCycle() const { return currentCycle; }
        int getSmId() const { return smId; }

        // Print method for debugging
        void printId() const { std::cout << "(ComputeUnit) ComputeUnit ID: " << smId << std::endl; }

        /// Method to calculate the next warp ID to execute based on round-robin scheduling
        void calculateNextWarpId();
        
};

#endif // COMPUTEUNIT_HH