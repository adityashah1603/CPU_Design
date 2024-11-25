#include "RegisterFile.h"

RegisterFile::RegisterFile(int numRegisters) {
        registers.resize(numRegisters, 0); // Initialize all registers to 0
    }

void RegisterFile::writeRegister(int regNum, uint16_t value) {
        if (regNum >= 0 && regNum < registers.size() && we_reg) {
            registers[regNum] = value;
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

uint16_t RegisterFile::readRegister(int regNum) {
    if (regNum >= 0 && regNum < registers.size()) {
        return registers[regNum];
    } else {
        std::cerr << "Error: Invalid register number.\n";
        return -1; // Return -1 to indicate an error
    }
}

void RegisterFile::displayRegisters() {
    for (int i = 0; i < registers.size(); ++i) {
        std::cout << "Register " << i << ": " << registers[i] << std::endl;
    }
}