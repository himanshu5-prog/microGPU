#include "warp.hh"

Warp::Warp() : id(0), pc(0), state(WarpState::READY), pipelineStage(PipelineStage::NOT_STARTED), isBranchDivergent(false) {
    std::cout << "Warp created with id: " << id << std::endl;
    activeMask.set();  // All threads active by default
}

Warp::Warp(int warpId, const ThreadGroup& threadGroup, WarpState warpState, PipelineStage pipelineStage, bool isBranchDivergent_)
    : id(warpId), pc(0), threads(threadGroup), state(warpState), pipelineStage(pipelineStage), isBranchDivergent(isBranchDivergent_) {
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

std::string Warp::getInstructionTypeString(Instruction inst) const {
    switch (inst.type) {
        case ADD: return "ADD";
        case SUB: return "SUB";
        case LOAD: return "LOAD";
        case STORE: return "STORE";
        default: return "UNKNOWN_INSTRUCTION";
    }
}

void Warp::execute(){
    Instruction instr = getCurrentInstruction();
    // Execute the instruction
    // Need to check active mask to determine which threads are active and should execute the instruction

    if (activeMask.none()) {
        std::cout << "(Warp " << id << ") No active threads to execute instruction." << std::endl;
        return;
    }
    int threadExecuted = 0;
    std:: cout << "(Warp " << id << ") Executing instruction: " << getInstructionTypeString(instr) << " with active mask: " << activeMask << std::endl;
    for (int t = 0; t < WARP_THREAD_COUNT; ++t) {
        // Check if the thread is active based on the active mask
        if (activeMask.test(t)) {
            threads[t].setState(ACTIVE);
            threads[t].setRegisterValue(instr.src1, 42); // Dummy execution: Set R0 to 42 for active threads
            threads[t].setRegisterValue(instr.src2, 24); // Dummy execution: Set R1 to 24 for active threads
            
            switch(instr.type) {
                case ADD:
                    threads[t].setRegisterValue(instr.dest, threads[t].getRegisterValue(instr.src1) + threads[t].getRegisterValue(instr.src2));
                    break;
                case SUB:
                    threads[t].setRegisterValue(instr.dest, threads[t].getRegisterValue(instr.src1) - threads[t].getRegisterValue(instr.src2));
                    break;
                case LOAD:
                    // Simulate a load by setting the destination register to a dummy value
                    threads[t].setRegisterValue(instr.dest, 123); // Dummy load value
                    break;
                case STORE:
                    // Simulate a store by printing the value being stored
                    std::cout << "(Warp " << id << ") Thread " << threads[t].getId() << " storing value: " << threads[t].getRegisterValue(instr.src1) <<
                                " to memory address: " << threads[t].getRegisterValue(instr.src2) << std::endl;
                    break;
                default:
                    std::cout << "(Warp " << id << ") Thread " << threads[t].getId() << " encountered unknown instruction type." << std::endl;
                // Branches will be handled in future iterations when we implement control flow and reconvergence
            }
            std::cout << "(Warp " << id << ") Thread " << threads[t].getId() << " is active and executed instruction: " << getInstructionTypeString(instr) << std::endl;
            threadExecuted += 1;
        } else {

            std::cout << "(Warp " << id << ") Thread " << threads[t].getId() << " is inactive and will not execute instruction." << std::endl;
        }
    }
    std::cout << "(Warp " << id << ") Executed instruction for " << threadExecuted << " threads." << std::endl;
}

void Warp::addReconvergencePoint(int pc, const ActiveMask& mask) {
    reconvergenceStack.emplace_back(pc, mask);
}

void Warp::peekReconvergencePoint() const {
    if (!reconvergenceStack.empty()) {
        const reconvergencePoint& top = reconvergenceStack.back();
        std::cout << "(Warp " << id << ") Top Reconvergence Point - PC: " << top.pc << ", Active Mask: " << top.mask << std::endl;
    } else {
        std::cout << "(Warp " << id << ") Reconvergence stack is empty." << std::endl;
        }
}

void Warp::popReconvergencePoint() {
    if (!reconvergenceStack.empty()) {
        reconvergenceStack.pop_back();
    } else {
        std::cout << "(Warp " << id << ") Cannot pop from empty reconvergence stack." << std::endl;
    }
}

size_t Warp::getReconvergenceStackSize() const {
    return reconvergenceStack.size();
}

std::bitset<WARP_THREAD_COUNT> Warp::getActiveMaskFromReconvergenceStack() const {
    if (!reconvergenceStack.empty()) {
        return reconvergenceStack.back().mask;
    } else {
        std::cout << "(Warp " << id << ") Reconvergence stack is empty. Returning default active mask." << std::endl;
        return std::bitset<WARP_THREAD_COUNT>().set(); // Default to all threads active if stack is empty
    }
}