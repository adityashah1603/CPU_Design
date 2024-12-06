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
    uint16_t getInstruction(const uint16_t &address);
private:
    ifstream InstructionFile;
    vector<uint16_t> instructions;
    int instructionCount;
    bool instructionsLoaded;
};