#ifndef MICROGPU_HH
#define MICROGPU_HH
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>

#include "../warp/warp.hh"
#include "../computeUnit/computeUnit.hh"

// Number of Compute Units in microGPU
#define CU_COUNT 16

class MicroGPU { 
   std::vector <Warp> globalWarpCollection;

   // Collection of Streaming Multiprocessors
   std::array<ComputeUnit, CU_COUNT> computeUnit;
   int currentCycle;
   int maxCycles;

   public:
        MicroGPU();
        void init();
        void assignWarpToSM(int smId, const Warp &warp);
        void addWarpToGlobalCollection(const Warp &warp);
        int getGlobalWarpCollectionSize() const;
        int getCurrentCycle() const { return currentCycle; }
        void incrementCycle() { currentCycle++; }
        void performWarpScheduling();
        void performWarpSchedulingSimple();
        void setMaxCycles(int cycles) { maxCycles = cycles; }

        // test method
        void createGlobalWarpCollectionTest();
        void printComputeUnitStatus() const;
        bool allComputeUnitsDone() const;
        bool allWarpsCompleted() const;
        void executeComputeUnits(); // Method to execute warps in compute units for one cycle
        void executeGPU(); // Method to execute the entire GPU until all warps are completed


};
#endif // MICROGPU_HH