#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>

class RegisterFile {
private:
    std::vector<uint16_t> registers; // Array to hold the registers
    bool we_reg;
public:
    RegisterFile(int numRegisters) {
        registers.resize(numRegisters, 0); // Initialize all registers to 0
        we_reg = false;
    }

    void writeRegister(int regNum, uint16_t value);
    uint16_t readRegister(int regNum);
    void displayRegisters();
};