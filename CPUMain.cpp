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

const uint16_t opcodeMask {0xF000};
const uint16_t sourceRegMask {0x0F00};
const uint16_t reg2Mask {0x00F0};
const uint16_t functMask {0x000F};

static uint16_t programCounter {0};
static uint16_t instructionRegister {0xFFFF};
static uint16_t returnAddressRegister {0};
static uint16_t stackPointerRegister {0};
static uint16_t hiRegister {0};
static uint16_t loRegister {0};

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
    while(!IMemModule.openInstructionFile()) {
        cin >> instructionFileName;
    }
    cout << "Successfully opened instructions!" << endl;

    IMemModule.loadInstructionsFromFile();

    

    while(instructionRegister != 0) { 
        // FETCH INSTRUCTION
        instructionRegister = IMemModule.getInstruction(programCounter);

        // DECODE INSTRUCTION
        uint8_t opcode {(instructionRegister & opcodeMask) >> 12};
        uint8_t funct {instructionRegister & functMask};
        if(opcode == )
        ControlModule.setOpcode(opcode);
        ControlModule.setFunct(funct);
        ControlModule.decodeOpcode();
        ControlSignals instructionSignals = ControlModule.getControlSignals();




    }

    return 1;
}