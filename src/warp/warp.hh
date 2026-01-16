#ifndef SRC_WARP_WARP_HH
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

using ThreadGroup = std::array<Thread*, WARP_THREAD_COUNT>;
using ActiveMask = std::bitset<WARP_THREAD_COUNT>;

class Warp {
    int id;
    int pc;
    ThreadGroup threads;
    ActiveMask activeMask;

    public:
    Warp();
    Warp(int warpId, const ThreadGroup& threadGroup);
    int getId() const;
    int getPc() const;
    void setPc(int pc_);

    const ActiveMask& getActiveMask() const;

};


#endif  // SRC_WARP_WARP_HH_
