#include "microGPU/ugpu.hh"

int main(){
    MicroGPU ugpu;
    ugpu.init();
    ugpu.createGlobalWarpCollectionTest();
    std :: cout << "(system) Now performing warp scheduling..." << std :: endl;
    ugpu.performWarpScheduling();
    ugpu.printComputeUnitStatus();
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