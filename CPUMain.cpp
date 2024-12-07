#include <iostream>
#include <string>

#include "ControlUnit.h"
#include "RegisterFile.h"
#include "ALU.h"
#include "DMem.h"
#include "IMem.h"

using std::cout;
using std::cin;
using std::string;
using std::cerr;
using std::endl;

typedef struct {
    bool overflow;
    bool zero;
} ALUFlags;

static const uint16_t opcodeMask {0xF000};
static const uint16_t destinationRegMask {0x0F00};
static const uint16_t sourceRegMask {0x00F0};
static const uint16_t jumpAddressMask {0x0FFF};
static const uint16_t functMask {0x000F};
static const uint16_t offsetMask {0x000F};
static const uint16_t immediateMask {0x00FF};
static const uint16_t returnAddressRegister { 14 };
static const uint16_t stackPointer { 15 };

static uint16_t programCounter {0x0000};
static uint16_t instructionRegister {0xFFFF};

static uint16_t hiRegister {0x0000};
static uint16_t loRegister {0x0000};

static ALUFlags flagRegister {false, false};

int main() {
    ControlUnit ControlModule;
    ALU ALUModule;
    InstructionMemory IMemModule;
    DataMemory DMemModule;
    RegisterFile RegFileModule(16);

    cout << "Welcome to 16-bit MIPS LITE!" << endl;
    cout << "============================" << endl;
    cout << "Please enter instructions file name: ";
    string instructionFileName;
    cin >> instructionFileName;
    while(!IMemModule.openInstructionFile(instructionFileName.c_str())) {
        cin >> instructionFileName;
    }
    cout << "Successfully opened instructions!" << endl;

    IMemModule.loadInstructionsFromFile();

    while(instructionRegister != 0) { 
        // FETCH INSTRUCTION
        instructionRegister = IMemModule.getInstruction(programCounter);

        // DECODE INSTRUCTION
        uint8_t sourceReg {0};
        uint8_t destReg {0};
        uint16_t jumpAddr {0};
        uint8_t immediateValue {0};

        uint8_t opcode {(instructionRegister & opcodeMask) >> 12};
        uint8_t funct {instructionRegister & functMask};
        ControlModule.setOpcode(opcode);
        ControlModule.setFunct(funct);
        ControlModule.decodeOpcode();
        ControlSignals instructionSignals = ControlModule.getControlSignals();
        if(opcode == 0b0011) { // I-Type Instruction
            destReg = (instructionRegister & destinationRegMask) >> 8;
            immediateValue = instructionRegister & immediateMask;
        }
        else { // R-Type Instruction
            sourceReg = (instructionRegister & sourceRegMask) >> 4;
            destReg = (instructionRegister & destinationRegMask) >> 8;
        }

        if(instructionSignals.jump) {
            programCounter = instructionRegister & jumpAddressMask;
            continue;
        }

        // EXECUTE INSTRUCTION
        int16_t destRegData {RegFileModule.readRegister(destReg)};
        int16_t sourceRegData;
        int16_t ALUResult;

        if(instructionSignals.alu_src) {
            sourceRegData = immediateValue;
        }
        else {
            sourceRegData = RegFileModule.readRegister(sourceReg);
        }

        ALUModule.compute(instructionSignals.alu_ctrl, destRegData, sourceRegData, ALUResult, flagRegister.overflow, flagRegister.zero);
        
        // MEMORY STAGE
        DMemModule.writeDataToMemory(ALUResult, sourceRegData, instructionSignals.we_dm);


        // WRITE BACK STAGE
        uint16_t dataMemData {DMemModule.getData(ALUResult)};

        if(!instructionSignals.dm2reg && instructionSignals.reg_dst) { // JAL instruction saves next address to $ra register (14)
            RegFileModule.writeRegister(returnAddressRegister, ALUResult, instructionSignals.we_reg);
        }
        else if(instructionSignals.dm2reg && !instructionSignals.reg_dst) { // LW instruction gets data from DMem to destReg
            RegFileModule.writeRegister(destReg, dataMemData, instructionSignals.we_reg);
        }
        else {
            RegFileModule.writeRegister(destReg, ALUResult, instructionSignals.we_reg); // R and I Type Instructions
        }

        programCounter++;
    }

    cout << "Program has finished execution. Final register values displayed below." << endl;
    RegFileModule.displayRegisters();
    
    return 1;
}