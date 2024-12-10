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

static const uint16_t opcodeMask {static_cast<uint16_t>(0xF000)};
static const uint16_t destinationRegMask {0x0F00};
static const uint16_t sourceRegMask {0x00F0};
static const uint16_t jumpAddressMask {0x0FFF};
static const uint16_t functMask {0x000F};
static const uint16_t offsetMask {0x000F};
static const uint16_t branchOffsetMask {0x00FF};
static const uint16_t immediateMask {0x00FF};
static const uint16_t shamtMask {0x00F0};
static const uint16_t returnAddressRegister { 14 };
static const uint16_t stackPointer { 15 };

static uint16_t programCounter {0x0000};
static uint16_t instructionRegister {static_cast<uint16_t>(0xFFFF)};

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
    string instructionFileName = "/Users/peterxiong/Documents/Programs/School/SJSU/CMPE-220/CPU/CPU/out.txt";
//    cin >> instructionFileName;
    while(!IMemModule.openInstructionFile(instructionFileName.c_str())) {
        cin >> instructionFileName;
    }
    cout << "Successfully opened instructions!" << endl;

    IMemModule.loadInstructionsFromFile();

    while(instructionRegister != 0) {
        // FETCH INSTRUCTION
        instructionRegister = IMemModule.getInstruction(programCounter);
        std::bitset<16> bin(instructionRegister);
        cout << "Program Counter: " << programCounter << " | Instruction: " << bin << endl;
        if(!instructionRegister) {
            continue;
        }
        // DECODE INSTRUCTION
        uint8_t sourceReg {0};
        uint8_t destReg {0};
        uint16_t jumpAddr {0};
        int8_t immediateValue {0};
        int8_t offsetValue {0};
        uint8_t shiftAmount {0};
        int8_t branchOffset {0};

        uint8_t opcode = static_cast<uint8_t>((uint16_t)(instructionRegister & opcodeMask) >> 12);
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
            if(instructionSignals.alu_ctrl == ALU_SLL || instructionSignals.alu_ctrl == ALU_SRL) {
                shiftAmount = (instructionRegister & shamtMask) >> 4; // Shift instructions use the Rs slot for a shift amount
            }
        }
        else { // I-Type Instructions
            destReg = (instructionRegister & destinationRegMask) >> 8;
            sourceReg = (instructionRegister & sourceRegMask) >> 4;
            immediateValue = (instructionRegister);
            if(opcode == 0b0001 || opcode == 0b0010) { // LW and SW need to save offset
                offsetValue = instructionRegister & offsetMask;
            }
            if(instructionSignals.branch) {
                branchOffset = instructionRegister & branchOffsetMask;
            }
        }
        programCounter++;
        if(instructionSignals.jump) { // For jump instructions, save the jump Address
            jumpAddr = instructionRegister & jumpAddressMask;
            if(instructionSignals.jr) jumpAddr = RegFileModule.readRegister(destReg);
            if(instructionSignals.jal) RegFileModule.writeRegister(14, programCounter, 1);
            programCounter = jumpAddr;
            continue;
        }
        if(instructionSignals.mflo) {
            RegFileModule.writeRegister(destReg, loRegister, 1);
            continue;
        }
        else if(instructionSignals.mfhi) {
            RegFileModule.writeRegister(destReg, hiRegister, 1);
            continue;
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
            else if(opcode == 0b0110) { //lui
                ALUOp1 = immediateValue << 8;
                ALUOp2 = 0;
            }
            
            else if(opcode == 0b1011) { //li
                ALUOp1 = immediateValue;
                ALUOp2 = 0;
            }
            
            else if(opcode == 0b1000) { //bis
                ALUOp1 = destRegData;
                ALUOp2 = 1;
            }
            
            else if(opcode == 0b1001) { //bns
                ALUOp1 = destRegData;
                ALUOp2 = 0;
            }
            
            else { // All other I-type instructions use this format
                ALUOp1 = destRegData;
                ALUOp2 = immediateValue;
            }
        }
        else {
            
            ALUOp1 = destRegData;
            if(instructionSignals.alu_ctrl == ALU_SLL || instructionSignals.alu_ctrl == ALU_SRL) {
                    ALUOp2 = shiftAmount;
            }
            else {
                ALUOp2 = sourceRegData;
            }
        }

        ALUModule.compute(instructionSignals.alu_ctrl, ALUOp1, ALUOp2, ALUResult, flagRegister.overflow, flagRegister.zero, hiRegister);
        
        if (opcode == 0b0000 && (funct == 0b0110 || funct == 0b0111))
            loRegister = ALUResult;
        if(instructionSignals.branch && ALUResult) { // Branch
            programCounter += branchOffset;
            continue;
        }

        // MEMORY STAGE
        if(instructionSignals.we_dm) {
            DMemModule.writeDataToMemory(ALUResult, destRegData, instructionSignals.we_dm);
        }
        int16_t dataMemData = 0;
        // WRITE BACK STAGE
        if (instructionSignals.dm2reg) {
            dataMemData = DMemModule.getData(ALUResult);
        }

        if(!instructionSignals.dm2reg && instructionSignals.reg_dst) { // JAL instruction saves next address to $ra register (14)
            RegFileModule.writeRegister(returnAddressRegister, ALUResult, instructionSignals.we_reg);
        }
        else if(instructionSignals.dm2reg && !instructionSignals.reg_dst) { // LW instruction gets data from DMem to destReg
            RegFileModule.writeRegister(destReg, dataMemData, instructionSignals.we_reg);
        }
        // else if(instructionSignals.mfhi) { // MFHI moves contents of hi register to destination
        //     RegFileModule.writeRegister(destReg, hiRegister, instructionSignals.we_reg);
        // }
        // else if(instructionSignals.mflo) { // MFLO moves contents of lo register to destination
        //     RegFileModule.writeRegister(destReg, ALUResult, instructionSignals.we_reg);
        // }
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
