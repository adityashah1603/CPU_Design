#include <iostream>
#include <string>
#include "IMem.h"

using std::getline;
using std::string;
using std::stoi;
using std::cerr;
using std::endl;

uint16_t InstructionMemory::getInstruction(const uint16_t &address) {
    uint16_t instruction {0b0};
    string FileLine;

    if(InstructionFile.is_open()) {
        InstructionFile.seekg(std::ios::beg);
        for(int line {0}; line <= address; line++) {
            getline(InstructionFile, FileLine);
        }

        instruction = stoi(FileLine,0,16);
    }
    else {
        cerr << "Error reading instruction. Instruction File not specified!" << endl;
    }

    return instruction;
}