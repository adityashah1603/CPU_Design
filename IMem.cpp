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
    instructionCount = 0;
    instructionsLoaded = false;
}

InstructionMemory::InstructionMemory(const char* filename) { 
    InstructionFile.open(filename); 
    if(!InstructionFile.is_open()) {
        cerr << "Error: Instruction File could not be opened." << endl;
    }
    instructions.resize(UINT16_MAX);
    instructionCount = 0;
    instructionsLoaded = false;
}

bool InstructionMemory::openInstructionFile(const char* filename) {
    InstructionFile.open(filename);
    if(!InstructionFile.is_open()) {
        cerr << "Error: Instruction File could not be opened." << endl;
        return false;
    }
    else
        return true;
}

void InstructionMemory::loadInstructionsFromFile() {
    if(!InstructionFile.is_open()) {
        cerr << "Error: Instruction File isn't open!." << endl;
    }
    else {
        string fileLine;
        uint16_t instructionAddress {0};
        while(getline(InstructionFile, fileLine)) {
            instructions[instructionAddress] = stoi(fileLine, 0, 2); // Stores instructions in binary format
            instructionAddress++;
            instructionCount++;
        }
        instructionsLoaded = true;
        }
}

uint16_t InstructionMemory::getInstruction(const uint16_t &address) {
    uint16_t returnInstruction {0b0};
    if(address < instructionCount && instructionsLoaded) {
        returnInstruction = instructions[address];
    }
    else {
        cerr << "Error: Could not fetch instruction." << endl;
    }
    return returnInstruction;
}