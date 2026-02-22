#ifndef MICROGPU_HH
#define MICROGPU_HH
#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>

#include "../warp/warp.hh"
#include "../computeUnit/computeUnit.hh"

/// Number of Compute Units in microGPU
#define CU_COUNT 16
/**
 * @defgroup Architecture
 * @brief Represents architectural components of a GPU, including ComputeUnit and the MicroGPU itself.
 */
/**
 * @brief Represents a microGPU
 * @ingroup Architecture
 * The MicroGPU class encapsulates the state and behavior of a microGPU, which consists of multiple compute units (CUs) that execute warps of threads.
 * In this project miroGPU has 16 compute units, each capable of executing one warp at a time. 
 * MicroGPU schedules warps from its global warp collection to the compute units and then Compute Units execute the warps in a simple round-robin fashion.
 * 
 */
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

        /**
         * @brief Add a warp to the global warp collection
         * 
         * @param warp The warp to be added to the global collection
         *
         */
        void addWarpToGlobalCollection(const Warp &warp);
        int getGlobalWarpCollectionSize() const;
        int getCurrentCycle() const { return currentCycle; }
        void incrementCycle() { currentCycle++; }
        void performWarpScheduling();

        /**
         * @brief Perform simple warp scheduling
         * This function assigns alternating warps from the global collection to the first two compute units in a round-robin fashion.
         * Just for testing purposes to verify that warps are being scheduled and executed correctly. In real life, all Compute Units would be utilized.
         */
        void performWarpSchedulingSimple();
        void setMaxCycles(int cycles) { maxCycles = cycles; }

        // test method
        /**
         *  @brief Create a Global Warp Collection Test object
         * This method creates a set of test warps with simple instructions and adds them to the global warp collection for testing purposes. Each warp is initialized with a simple ADD instruction and all threads in the warp are set to active.
         * Additionally, one warp with a branch instruction is added to test divergence handling in the compute units.
         * 
         */
        void createGlobalWarpCollectionTest();
        void printComputeUnitStatus() const;
        bool allComputeUnitsDone() const;
        bool allWarpsCompleted() const;

        /**
         * @brief Execute all compute units for one cycle
         * 
         */
        void executeComputeUnits(); // Method to execute warps in compute units for one cycle

        /**
         * @brief Execute the entire GPU until all warps are completed
         * 
         */
        void executeGPU(); // Method to execute the entire GPU until all warps are completed


};
#endif // MICROGPU_HH