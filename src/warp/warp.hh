#ifndef SRC_WARP_WARP_HH_
#define SRC_WARP_WARP_HH_

#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<bitset>
#include "../thread/thread.hh"

#define WARP_THREAD_COUNT 32

enum InstructionType {
    ADD,
    SUB,
    LOAD,
    STORE,
    BRANCH
};

//Instruction structure
struct Instruction {
    InstructionType type;
    int dest;
    int src1;
    int src2;

    Instruction(InstructionType t, int d, int s1, int s2)
        : type(t), dest(d), src1(s1), src2(s2) {}
    Instruction() : type(ADD), dest(0), src1(0), src2(0) {}

};

struct reconvergencePoint {
    int pc;
    ActiveMask mask;

    reconvergencePoint(int pc_, const ActiveMask& mask_)
        : pc(pc_), mask(mask_) {}
    reconvergencePoint() : pc(0), mask() {}
};

enum WarpState {
    READY,
    RUNNING,
    STALLED
};

using ThreadGroup = std::array<Thread*, WARP_THREAD_COUNT>;
using ActiveMask = std::bitset<WARP_THREAD_COUNT>;

class Warp {
    int id;
    int pc;
    ThreadGroup threads;
    ActiveMask activeMask;
    Instruction currentInstruction;
    std::vector<reconvergencePoint> reconvergenceStack;
    WarpState state;

    public:
    Warp();
    Warp(int warpId, const ThreadGroup& threadGroup, WarpState warpState = WarpState::READY);

     // Getter and Setter methods
    int getId() const;
    int getPc() const;
    void setPc(int pc_);
    void setCurrentInstruction(const Instruction& instr);
    Instruction getCurrentInstruction() const;

    const ActiveMask& getActiveMask() const;

};


#endif  // SRC_WARP_WARP_HH_
