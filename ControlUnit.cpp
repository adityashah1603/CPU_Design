#include "ControlUnit.h"
#include <iostream>

using std::cerr;
using std::endl;

void ControlUnit::setOpcode(uint8_t inputOpcode) {
    if(inputOpcode > 0b1111) {
        cerr << "Error writing opcode. Out of range." << endl;
        return;
    }
    opcode = inputOpcode;
}

void ControlUnit::setFunct(uint8_t inputFunct) {
    if(inputFunct > 0b1111) {
        cerr << "Error writing funct. Out of range." << endl;
        return;
    }
    funct = inputFunct;
}

void ControlUnit::clearControlSignals() {
    control.RegDst;
    control.ALUSrc;
    control.MemToReg;
    control.RegWrite;
    control.MemRead;
    control.MemWrite;
    control.Branch;
    control.Jump;
    control.AluOp;
}

ControlSignals ControlUnit::generateControls() {
    clearControlSignals();
    switch(opcode) {
    
    case(0b0001):

    case(0b0010):
    
    case(0b0011):

    case(0b0100):

    case(0b0101):

    case(0b0110):
    
    case(0b0111):

    case(0b1000):

    case(0b1001):

    case(0b1010):

    case(0b1011):

    case(0b1100):

    case(0b1101):

    case(0b1110):

    case(0b1111):


    }
}