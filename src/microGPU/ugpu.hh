#ifndef MICROGPU_HH
#define MICROGPU_HH
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>

#include "../warp/warp.hh"
#include "../computeUnit/computeUnit.hh"

#define SM_COUNT 16

class MicroGPU { 
   std::vector <Warp> globalWarpCollection;

   // Collection of Streaming Multiprocessors
   std::array<ComputeUnit, SM_COUNT> computeUnit;

   public:
        MicroGPU();
        void init();
        void assignWarpToSM(int smId, const Warp &warp);
        void addWarpToGlobalCollection(const Warp &warp);
        int getGlobalWarpCollectionSize() const;


};
#endif // MICROGPU_HH