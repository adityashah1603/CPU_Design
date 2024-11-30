#include <iostream>
#include <string>
#include "IMem.h"

using std::getline;
using std::string;
using std::stoi;
using std::cerr;
using std::endl;

InstructionMemory::InstructionMemory() {
    instructions.resize(UINT16_MAX);
}

InstructionMemory::InstructionMemory(const char* filename) { 
    InstructionFile.open(filename); 
    if(!InstructionFile.is_open()) {

    }
    instructions.resize(UINT16_MAX);
}
void InstructionMemory::openInstructionFile(const char* filename) {
    InstructionFile.open(filename);
    if(!InstructionFile.is_open()) {
        cerr << "Error: Instruction File could not be opened." << endl;
    }
}

void InstructionMemory::loadInstructionsFromFile() {
    if(!InstructionFile.is_open()) {
        cerr << "Error: Instruction File could not be opened." << endl;
    }
    else {
        string fileLine;
        uint16_t instructionAddress {0};
        while(getline(InstructionFile, fileLine))
            instructions[instructionAddress] = stoi(fileLine, 0, 16); // Stores instructions in hex format
            instructionAddress++;
        }
}

uint16_t InstructionMemory::getInstruction(const uint16_t &address) {
    uint16_t returnInstruction {0b0};
    if(address < UINT16_MAX) {
        returnInstruction = instructions[address];
    }
    return returnInstruction;
}