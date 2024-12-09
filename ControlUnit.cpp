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
}

void ControlUnit::setOpcode(int8_t inputOpcode) {
    if(inputOpcode > 0b1111) {
        cerr << "Error writing opcode. Out of range." << endl;
        return;
    }
    opcode = inputOpcode;
}

void ControlUnit::setFunct(int8_t inputFunct) {
    if(inputFunct > 0b1111) {
        cerr << "Error writing funct. Out of range." << endl;
        return;
    }
    funct = inputFunct;
}

void ControlUnit::clearControlSignals() {
    control = {false, false, false, false, false, false, false, false, ALU_ADD};
}

ALUOperations ControlUnit::functToALUOperation(const int8_t funct) {

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
        cerr<<"Error: Invalid function code"<<endl;
    }

    return returnOperation;
}

void ControlUnit::decodeOpcode() {
    clearControlSignals();
    switch(opcode) {
        case 0b0000: // R-Type
            control = {false, false, false, false, false, false, false, true, false, functToALUOperation(funct)};
            break;
        case 0b0001: // Store
            control = {false, false, true, false, false, false, true, false, false, ALU_ADD};
            break;
        case 0b0010: // Load
            control = {true, false, true, false, false, false, false, true, false, ALU_ADD};
            break;
        case 0b0011: // Jump
            control.jump = true;
            break;
        case 0b0100: // Jump Register
            control = 
            break;
        case 0b0101: // Jump and Link
            control = {false, true, }
            break;
        case 0b0110: // Load upper immediate
            control = 
            break;
        case 0b0111: // addi
            control = {false, false, true, false, false, false, false, true, false, ALU_ADD};
            break;
        case 0b1000: // Branch if set
            control = 
            break;
        case 0b1001: // Branch if not set
            control = 
            break;
        case 0b1010: // Load immediate
            control =
            break;
        case 0b1011: // Move from hi
            control = 
            break;
        case 0b1100: // Move from lo
            control = 
            break;
        default:
            cerr << "Error: Invalid opcode" << endl;
    }
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