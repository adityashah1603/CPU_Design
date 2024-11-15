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
    control.dm2reg = false;
    control.reg_dst = false;
    control.alu_src = false;
    control.jump = false;
    control.branch = false;
    control.pc_src = false;
    control.we_dm = false;
    control.we_reg = false;
    control.alu_ctrl = ALU_ADD;
}

ALUOperations ControlUnit::functToALUOperation(const uint8_t funct) {

    ALUOperations returnOperation;

    switch(funct) {
    case(0b0000):
        returnOperation = ALU_ADD;
        break;
    case(0b0001):
        returnOperation = ALU_SUB;
        break;
    case(0b0010):
        returnOperation = ALU_OR;
        break;
    case(0b0011):
        returnOperation = ALU_AND;
        break;
    case(0b0100):
        returnOperation = ALU_NOT;
        break;
    case(0b0101):
        returnOperation = ALU_XOR;
        break;
    case(0b0110):
        returnOperation = ALU_MULT;
        break;
    case(0b0111):
        returnOperation = ALU_DIV;
        break;
    case(0b1000):
        returnOperation = ALU_SLT;
        break;
    case(0b1001):
        returnOperation = ALU_SGT;
        break;
    case(0b1010):
        returnOperation = ALU_SLL;
        break;
    case(0b1011):
        returnOperation = ALU_SRL;
        break;
    default:
        returnOperation = ALU_ADD;
        break;
    }

    return returnOperation;
}

ControlSignals ControlUnit::generateControls() {
    clearControlSignals();
    switch(opcode) {
    
    case(0b0000): // R-Type Instruction
        control.dm2reg = false;
        control.reg_dst = false;
        control.alu_src = false;
        control.jump = false;
        control.branch = false;
        control.pc_src = false;
        control.we_dm = false;
        control.we_reg = false;
        alu_op = 0b10;
    break;


    }

    switch(alu_op) {
    case(0b00):
        control.alu_ctrl = ALU_ADD;
    case(0b01):
        control.alu_ctrl = ALU_SUB;
    default:
        control.alu_ctrl = functToALUOperation(funct);
    }
    
    return control;
}