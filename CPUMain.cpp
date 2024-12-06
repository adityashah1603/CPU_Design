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

static uint16_t programCounter {0x0000};
static uint16_t instructionRegister {0xFFFF};
static uint16_t returnAddressRegister {0x0000};
static uint16_t stackPointerRegister {0xFFFF};
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
        if(opcode == 0b0011) { // Jump Instruction
            jumpAddr = instructionRegister & jumpAddressMask;
        }
        else if(opcode == 0b0011) { // I-Type Instruction
            destReg = (instructionRegister & destinationRegMask) > 8;
            immediateValue = instructionRegister & immediateValue;
        }
        else {
            sourceReg = (instructionRegister & sourceRegMask) >> 4;
            destReg = (instructionRegister & destinationRegMask) >> 8;
        }

        // EXECUTE INSTRUCTION
        int16_t ALUOp1 {RegFileModule.readRegister(destReg)};
        int16_t ALUOp2;
        int16_t ALUResult;

        if(instructionSignals.alu_src) {
            ALUOp2 = immediateValue;
        }
        else {
            ALUOp2 = RegFileModule.readRegister(sourceReg);
        }

        ALUModule.compute(instructionSignals.alu_ctrl, ALUOp1, ALUOp2, ALUResult, flagRegister.overflow, flagRegister.zero);
        


        


    }

    return 1;
}