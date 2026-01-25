#include "warp.hh"

Warp::Warp() : id(0), pc(0), state(WarpState::READY) {
    std::cout << "Warp created with id: " << id << std::endl;
    activeMask.set();  // All threads active by default 
    threads.fill(nullptr);
}

Warp::Warp(int warpId, const ThreadGroup& threadGroup, WarpState warpState)
    : id(warpId), pc(0), threads(threadGroup), state(warpState) {
    std::cout << "Warp created with id: " << id << std::endl;
    activeMask.set();  // All threads active by default
}

int Warp::getId() const {
    return id;
}

int Warp::getPc() const {
    return pc;
}

void Warp::setPc(int pc_) {
    pc = pc_;
}

const ActiveMask& Warp::getActiveMask() const {
    return activeMask;
}

void Warp::setCurrentInstruction(const Instruction& instr) {
    currentInstruction = instr;
}

Instruction Warp::getCurrentInstruction() const {
    return currentInstruction;
}

