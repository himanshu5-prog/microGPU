#include "thread.hh"

Thread::Thread() : id(0), state(INACTIVE) {
    std::cout << "Thread created with id: " << id << std::endl;
}

Thread::Thread(int threadId, ThreadState threadState){
    id = threadId;
    state = threadState;
    std::cout << "Thread created with id: " << id << std::endl;

}

// Getter methods
int Thread::getId() const {
    return id;
}

ThreadState Thread::getState() const {
    return state;
}


int Thread::getRegisterValue(int index) const {
    assert(index >= 0 && index < THREAD_REGISTER_COUNT && "Register index out of bounds");
    return registers[index];
}

// Setter methods
void Thread::setId(int threadId) {
    id = threadId;
}

void Thread::setState(ThreadState threadState) {
    state = threadState;
}


void Thread::setRegisters(const RegisterFile& regs) {
    registers = regs;
}

void Thread::setRegisterValue(int index, int value) {
    assert(index >= 0 && index < THREAD_REGISTER_COUNT && "Register index out of bounds");
    registers[index] = value;
}
