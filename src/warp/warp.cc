#include "warp.hh"

Warp::Warp() : id(0), pc(0) {
    std::cout << "Warp created with id: " << id << std::endl;
    activeMask.set();  // All threads active by default 
    threads.fill(nullptr);
}

Warp::Warp(int warpId, const ThreadGroup& threadGroup)
    : id(warpId), pc(0), threads(threadGroup) {
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

