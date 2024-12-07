#include "ControlUnit.h"
#include <iostream>
#include <bitset>

using std::cerr;
using std::cout;
using std::endl;
using std::bitset;

ControlUnit::ControlUnit() {
    opcode = funct = alu_op = 0;
    clearControlSignals();
    // opcode = 0b0000;
    // funct = 0b0000;
    // alu_op = 0b00;
    // control.dm2reg = false;
    // control.reg_dst = false;
    // control.alu_src = false;
    // control.jump = false;
    // control.branch = false;
    // control.pc_src = false;
    // control.we_dm = false;
    // control.we_reg = false;
    // control.alu_ctrl = ALU_ADD;
}

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
    control = {false, false, false, false, false, false, false, false, ALU_ADD};
    // control.dm2reg = false;
    // control.reg_dst = false;
    // control.alu_src = false;
    // control.jump = false;
    // control.branch = false;
    // control.pc_src = false;
    // control.we_dm = false;
    // control.we_reg = false;
    // control.alu_ctrl = ALU_ADD;
}

ALUOperations ControlUnit::functToALUOperation(const uint8_t funct) {

    ALUOperations returnOperation;
    cout << "Inside functToALU" << endl;
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
        // returnOperation = ALU_ADD;
        cerr<<"Error: Invalid function code"<<endl;
        throw invalid_argument("Invalid function code");
        // break;
    }

    // return returnOperation;
}

void ControlUnit::decodeOpcode() {
    clearControlSignals();
    switch(opcode) {
    case(0b0000): // R-Type Instruction
        control.dm2reg = false;
        control.reg_dst = true;
        control.alu_src = false;
        control.jump = false;
        control.branch = false;
        control.pc_src = false;
        control.we_dm = false;
        control.we_reg = true;
        alu_op = 0b10;
        break;

    case(0b0010): // Load Instruction
        control.dm2reg = true;
        control.reg_dst = false;
        control.alu_src = true;
        control.jump = false;
        control.branch = false;
        control.pc_src = false;
        control.we_dm = false;
        control.we_reg = true;
        alu_op = 0b00;
        break;

    case(0b0001): // Save Instruction
        control.dm2reg = false;
        control.reg_dst = false;
        control.alu_src = true;
        control.jump = false;
        control.branch = false;
        control.pc_src = false;
        control.we_dm = true;
        control.we_reg = false;
        alu_op = 0b00;
        break;

    case(0b0011): // I-Type Instruction
        control.dm2reg = false;
        control.reg_dst = false;
        control.alu_src = true;
        control.jump = false;
        control.branch = false;
        control.pc_src = false;
        control.we_dm = false;
        control.we_reg = true;
        alu_op = 0b00;
        break;

    case(0b0100): // Branch Instruction
        control.dm2reg = false;
        control.reg_dst = false;
        control.alu_src = false;
        control.jump = false;
        control.branch = true;
        control.pc_src = false;
        control.we_dm = false;
        control.we_reg = false;
        alu_op = 0b01;
        break;

    case(0b0101): // Jump Instruction
        control.dm2reg = false;
        control.reg_dst = false;
        control.alu_src = false;
        control.jump = true;
        control.branch = false;
        control.pc_src = false;
        control.we_dm = false;
        control.we_reg = false;
        alu_op = 0b01;
        break;
=======
    // case(0b0000): // R-Type Instruction
    //     control.dm2reg = false;
    //     control.reg_dst = true;
    //     control.alu_src = false;
    //     control.jump = false;
    //     control.branch = false;
    //     control.pc_src = false;
    //     control.we_dm = false;
    //     control.we_reg = true;
    //     alu_op = 0b10;
    //     break;

    // case(0b0001): // Load Instruction
    //     control.dm2reg = true;
    //     control.reg_dst = false;
    //     control.alu_src = true;
    //     control.jump = false;
    //     control.branch = false;
    //     control.pc_src = false;
    //     control.we_dm = false;
    //     control.we_reg = true;
    //     alu_op = 0b00;
    //     break;

    // case(0b0010): // Save Instruction
    //     control.dm2reg = false;
    //     control.reg_dst = false;
    //     control.alu_src = true;
    //     control.jump = false;
    //     control.branch = false;
    //     control.pc_src = false;
    //     control.we_dm = true;
    //     control.we_reg = false;
    //     alu_op = 0b00;
    //     break;

    // case(0b0011): // I-Type Instruction
    //     control.dm2reg = false;
    //     control.reg_dst = false;
    //     control.alu_src = true;
    //     control.jump = false;
    //     control.branch = false;
    //     control.pc_src = false;
    //     control.we_dm = false;
    //     control.we_reg = true;
    //     alu_op = 0b00;
    //     break;

    // case(0b0100): // Branch Instruction
    //     control.dm2reg = false;
    //     control.reg_dst = false;
    //     control.alu_src = false;
    //     control.jump = false;
    //     control.branch = true;
    //     control.pc_src = false;
    //     control.we_dm = false;
    //     control.we_reg = false;
    //     alu_op = 0b01;
    //     break;

    // case(0b0101): // Jump Instruction
    //     control.dm2reg = false;
    //     control.reg_dst = false;
    //     control.alu_src = false;
    //     control.jump = true;
    //     control.branch = false;
    //     control.pc_src = false;
    //     control.we_dm = false;
    //     control.we_reg = false;
    //     alu_op = 0b01;
    //     break;
  
    case 0b0000: // R-Type
            control = {false, true, false, false, false, false, false, true, functToALUOperation(funct)};
            break;
        case 0b0001: // Load
            control = {true, false, true, false, false, false, false, true, ALU_ADD};
            break;
        case 0b0010: // Store
            control = {false, false, true, false, false, false, true, false, ALU_ADD};
            break;
        case 0b0011: // Jump
            control.jump = true;
            break;
        case 0b0100: // Branch
            control.branch = true;
            control.alu_ctrl = ALU_SUB;
            break;
        case 0b1000: // BIS
            control = {false, false, true, false, false, false, false, false, ALU_BIS};
            break;
        case 0b1001: // BNS
            control = {false, false, true, false, false, false, false, false, ALU_BNS};
            break;
        default:
            cerr << "Error: Invalid opcode" << endl;
            throw invalid_argument("Invalid opcode");
    }

    // switch(alu_op) {
    // case(0b00):
    //     control.alu_ctrl = ALU_ADD;
    //     break;
    // case(0b01):
    //     control.alu_ctrl = ALU_SUB;
    //     break;
    // default:
    //     control.alu_ctrl = functToALUOperation(funct);
    //     break;
    // }
}

void ControlUnit::printControls() const {
    cout << "Control Signals" << endl;
    cout << "===============" << endl;
    cout << std::boolalpha;
    cout << "opcode: " << bitset<4>(opcode) << endl;
    cout << "funct: " << bitset<4>(funct) << endl;
    cout << "we_reg: " << control.we_reg << endl;
    cout << "reg_dst: " << control.reg_dst << endl;
    cout << "alu_src: " << control.alu_src << endl;
    cout << "branch: " << control.branch << endl;
    cout << "we_dm: " << control.we_dm << endl;
    cout << "dm2reg: " << control.dm2reg << endl;
    cout << "alu_op: " << control.alu_ctrl << endl;
    cout << "jump: " << control.jump << endl;
}