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

static const int16_t opcodeMask {static_cast<int16_t>(0xF000)};
static const int16_t destinationRegMask {0x0F00};
static const int16_t sourceRegMask {0x00F0};
static const int16_t jumpAddressMask {0x0FFF};
static const int16_t functMask {0x000F};
static const int16_t offsetMask {0x000F};
static const int16_t immediateMask {0x00FF};
static const int16_t returnAddressRegister { 14 };
static const int16_t stackPointer { 15 };

static int16_t programCounter {0x0000};
static int16_t instructionRegister {static_cast<int16_t>(0xFFFF)};

static int16_t hiRegister {0x0000};
static int16_t loRegister {0x0000};

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
        if(instructionRegister) {
            programCounter++;
        }
        else {
            continue;
        }
        // DECODE INSTRUCTION
        int8_t sourceReg {0};
        int8_t destReg {0}; 
        int16_t jumpAddr {0};
        int8_t immediateValue {0};
        int8_t offsetValue {0};

        int8_t opcode {static_cast<int8_t>((instructionRegister & opcodeMask) >> 12)};
        int8_t funct;
        if(opcode == 0b0000) { // Funct is only used for R-type instructions
            funct = instructionRegister & functMask;
        }
        else {
            funct = 0;
        }
        
        ControlModule.setOpcode(opcode);
        ControlModule.setFunct(funct);
        ControlModule.decodeOpcode();
        ControlSignals instructionSignals = ControlModule.getControlSignals();
        if(opcode == 0b0000) { // R-Type Instructions
            sourceReg = (instructionRegister & sourceRegMask) >> 4;
            destReg = (instructionRegister & destinationRegMask) >> 8;
        }
        else { // I-Type Instructions
            destReg = (instructionRegister & destinationRegMask) >> 8;
            sourceReg = (instructionRegister & sourceRegMask) >> 4;
            immediateValue = (instructionRegister & immediateMask);
            if(opcode == 0b0001 || opcode == 0b0010) { // LW and SW need to save offset
                offsetValue = instructionRegister & offsetMask;
            }
        }

        if(instructionSignals.jump) {
            programCounter = instructionRegister & jumpAddressMask;
        }
        // EXECUTE INSTRUCTION
        int16_t destRegData {RegFileModule.readRegister(destReg)};
        int16_t sourceRegData {RegFileModule.readRegister(sourceReg)};
        int16_t ALUOp1;
        int16_t ALUOp2;
        int16_t ALUResult;

        if(instructionSignals.alu_src) { // I-Type
            if(opcode == 0b0001 || opcode == 0b0010) {
                ALUOp1 = sourceRegData; // For LW and SW, the address to save is stored in source reg value
                ALUOp2 = offsetValue; // For LW and SW, the offset to add to address in source reg
            }
            else { // All other I-type instructions use this format
                ALUOp1 = destRegData;
                ALUOp2 = immediateValue;
            }
        }
        else { // R-Type
            ALUOp1 = destRegData;
            ALUOp2 = sourceRegData;
        }


        ALUModule.compute(instructionSignals.alu_ctrl, ALUOp1, ALUOp2, ALUResult, flagRegister.overflow, flagRegister.zero, hiRegister);
        
        // MEMORY STAGE
        DMemModule.writeDataToMemory(ALUResult, destRegData, instructionSignals.we_dm);

        // WRITE BACK STAGE
        int16_t dataMemData {DMemModule.getData(ALUResult)};

        if(!instructionSignals.dm2reg && instructionSignals.reg_dst) { // JAL instruction saves next address to $ra register (14)
            RegFileModule.writeRegister(returnAddressRegister, ALUResult, instructionSignals.we_reg);
        }
        else if(instructionSignals.dm2reg && !instructionSignals.reg_dst) { // LW instruction gets data from DMem to destReg
            RegFileModule.writeRegister(destReg, dataMemData, instructionSignals.we_reg);
        }
        else {
            RegFileModule.writeRegister(destReg, ALUResult, instructionSignals.we_reg); // R and I Type Instructions
        }
    }

    cout << "Program has finished execution. Final register values displayed below." << endl;
    RegFileModule.displayRegisters();
    cout << "Please enter file name for data memory output." << endl;
    string outputFileName;
    cin >> outputFileName;
    DMemModule.openDataOutputFile(outputFileName);
    DMemModule.dumpDataToFile();
    
    return 1;
}