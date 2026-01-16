#ifndef SRC_THREAD_THREAD_HH_
#define SRC_THREAD_THREAD_HH_

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <array>
// Define the number of registers available to each thread
#define THREAD_REGISTER_COUNT 64

using RegisterFile = std::array<int, THREAD_REGISTER_COUNT>;

enum ThreadState {
    ACTIVE,
    INACTIVE
};

class Thread {
    int id;
    ThreadState state;
    RegisterFile registers;

public:

    Thread();
    Thread(int threadId, ThreadState threadState);

    // Getter methods
    int getId() const;
    ThreadState getState() const;
    int getRegisterValue(int index) const;

    // Setter methods
    void setId(int threadId);
    void setState(ThreadState threadState);
    void setRegisters(const RegisterFile& regs);
    void setRegisterValue(int index, int value);
};


#endif  // SRC_THREAD_THREAD_HH_
