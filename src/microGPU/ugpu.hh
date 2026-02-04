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

   public:
        MicroGPU();
        void init();
        void assignWarpToSM(int smId, const Warp &warp);
        void addWarpToGlobalCollection(const Warp &warp);
        int getGlobalWarpCollectionSize() const;
        int getCurrentCycle() const { return currentCycle; }
        void incrementCycle() { currentCycle++; }
        void performWarpScheduling();

        // test method
        void createGlobalWarpCollectionTest();
        void printComputeUnitStatus() const;
        bool allComputeUnitsDone() const;
        bool allWarpsCompleted() const;


};
#endif // MICROGPU_HH