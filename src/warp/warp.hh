#ifndef SRC_WARP_WARP_HH_
#define SRC_WARP_WARP_HH_

#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>
#include "../thread/thread.hh"

// Define the number of threads in a warp
#define WARP_THREAD_COUNT 32

// Type alias for the active mask of threads in a warp
using ActiveMask = std::bitset<WARP_THREAD_COUNT>;


/// Instruction types enumeration
enum InstructionType {
    ADD,
    SUB,
    LOAD,
    STORE,
    BRANCH
};

///Instruction structure
struct Instruction {
    InstructionType type;
    int dest;
    int src1;
    int src2;

    Instruction(InstructionType t, int d, int s1, int s2)
        : type(t), dest(d), src1(s1), src2(s2) {}
    Instruction() : type(ADD), dest(0), src1(0), src2(0) {}

};

// Reconvergence point structure
struct reconvergencePoint {
    int pc;
    ActiveMask mask;

    reconvergencePoint(int pc_, const ActiveMask& mask_)
        : pc(pc_), mask(mask_) {}
    reconvergencePoint() : pc(0), mask() {}
};

// Warp state enumeration
enum WarpState {
    READY,
    RUNNING,
    STALLED
};

enum PipelineStage {
    NOT_STARTED,
    STAGE_0,
    STAGE_1,
    STAGE_2,
    STAGE_3,
    DONE
};

// Type alias for a group of threads in a warp
using ThreadGroup = std::array<Thread, WARP_THREAD_COUNT>;

/**
 * @class Warp
 * @brief Represents a GPU warp
 * @ingroup Computation
 * The Warp class encapsulates the state and behavior of a GPU warp, including its ID, program counter, threads, active mask, and current instruction.
 * A warp is a group of threads that execute instructions in lockstep. Each warp has 32 threads in this project. 
 * To be added: reconvergence stack to handle divergent control flow.
 */
class Warp {
    int id;
    int pc; // All threads in the warp share the same program counter
    ThreadGroup threads;
    ActiveMask activeMask;
    Instruction currentInstruction;
    std::vector<reconvergencePoint> reconvergenceStack;
    WarpState state;
    PipelineStage pipelineStage;

    public:
    Warp();
    Warp(int warpId, const ThreadGroup& threadGroup, WarpState warpState = WarpState::READY, PipelineStage pipelineStage = PipelineStage::NOT_STARTED);

     // Getter and Setter methods
    int getId() const;
    int getPc() const;
    void setPc(int pc_);
    void setCurrentInstruction(const Instruction& instr);
    Instruction getCurrentInstruction() const;
    PipelineStage getPipelineStage() const { return pipelineStage; }
    void setPipelineStage(PipelineStage stage) { pipelineStage = stage; }
    void setActiveMask(const ActiveMask& mask) { activeMask = mask; }
    std :: string getPipelineStageString() const;
    const ActiveMask& getActiveMask() const;
    WarpState getState() const { return state; }

};


#endif  // SRC_WARP_WARP_HH_
