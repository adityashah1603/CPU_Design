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
    RegisterFile(int numRegisters);

    void writeRegister(uint16_t regNum, uint16_t value);
    uint16_t readRegister(uint16_t regNum);
    void displayRegisters();
};