#pragma once
#include <fstream>
#include <cstdint>
#include <vector>

using std::ifstream;
using std::vector;

class InstructionMemory {

public:
    InstructionMemory();
    InstructionMemory(const char* filename);
    ~InstructionMemory() { InstructionFile.close(); }
    bool openInstructionFile(const char* filename);
    void loadInstructionsFromFile();
    int16_t getInstruction(const int16_t &address);
private:
    ifstream InstructionFile;
    vector<int16_t> instructions;
    int instructionCount;
    bool instructionsLoaded;
};