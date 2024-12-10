#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>

class RegisterFile {
private:
    std::vector<int16_t> registers; // Array to hold the registers
public:
    RegisterFile(int numRegisters);

    void writeRegister(uint16_t regNum, int16_t value, bool we_reg);
    int16_t readRegister(uint16_t regNum);
    void displayRegisters();
};
