#include "microGPU/ugpu.hh"
#define SIMULATION_CYCLES 100

int main(){
    MicroGPU ugpu;

    // Initialize microGPU and compute units
    ugpu.init();

    // Create some test warps and add them to the global collection
    ugpu.createGlobalWarpCollectionTest();

    // Perform warp scheduling to assign warps to compute units
    std :: cout << "(system) Now performing warp scheduling..." << std :: endl;
    ugpu.performWarpSchedulingSimple();

    // Simulate execution for aSIMULATION_CYCLES cycles
    for (int cycle = 0; cycle < SIMULATION_CYCLES; ++cycle) {
        std::cout << "\n--- Simulation Cycle: " << cycle << " ---\n";
        // Execute warps in compute units for one cycle
        ugpu.executeComputeUnits();
        
        // Check if all warps have completed execution
        if (ugpu.allWarpsCompleted()) {
            std::cout << "(system) All warps have completed execution. Ending simulation at cycle:  " << cycle << std::endl;
            break;
        }
    }
    // Execution completed, print final status of compute units
    //ugpu.printComputeUnitStatus();
    return 0;    
}

// A little bit about microGPU
/*
The microGPU class represents a simplified model of a GPU architecture, 
focusing on the management of warps and computing units.
It contains a global collection of warps and an array of compute units.

1.  Global Warp Collection: It has a vector to store all warps that are part of the GPU's workload.
This allows for centralized management and tracking of warps.

2. The above warp collection is sent to each compute unit for processing.

3. Compute Units: Compute units process the  warps assigned to them. 
Each compute unit can manage its own state and the warps it is responsible for executing.
*/