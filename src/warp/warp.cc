#include "warp.hh"

Warp::Warp() : id(0), pc(0), state(WarpState::READY), pipelineStage(PipelineStage::NOT_STARTED) {
    std::cout << "Warp created with id: " << id << std::endl;
    activeMask.set();  // All threads active by default 
}

Warp::Warp(int warpId, const ThreadGroup& threadGroup, WarpState warpState, PipelineStage pipelineStage)
    : id(warpId), pc(0), threads(threadGroup), state(warpState), pipelineStage(pipelineStage) {
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

std::string Warp::getPipelineStageString() const {
    switch (pipelineStage) {
        case NOT_STARTED: return "NOT_STARTED";
        case STAGE_0: return "STAGE_0";
        case STAGE_1: return "STAGE_1";
        case STAGE_2: return "STAGE_2";
        case STAGE_3: return "STAGE_3";
        case DONE: return "DONE";
        default: return "UNKNOWN_STAGE";
    }
}
