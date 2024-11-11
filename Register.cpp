#include <iostream>
#include <vector>
#include <unordered_map>

class RegisterFile {
private:
    std::vector<int> registers; // Array to hold the registers
    std::unordered_map<int, int> memory; // Simple memory storage using a map

public:
    RegisterFile(int numRegisters) {
        registers.resize(numRegisters, 0); // Initialize all registers to 0
    }

    void writeRegister(int regNum, int value) {
        if (regNum >= 0 && regNum < registers.size()) {
            registers[regNum] = value;
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

    int readRegister(int regNum) {
        if (regNum >= 0 && regNum < registers.size()) {
            return registers[regNum];
        } else {
            std::cerr << "Error: Invalid register number.\n";
            return -1; // Return -1 to indicate an error
        }
    }

    void store(int regNum, int address) {
        if (regNum >= 0 && regNum < registers.size()) {
            memory[address] = registers[regNum];
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

    void load(int regNum, int address) {
        if (regNum >= 0 && regNum < registers.size()) {
            registers[regNum] = memory[address];
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

    void addi(int regNum, int immediateValue) {
        if (regNum >= 0 && regNum < registers.size()) {
            registers[regNum] += immediateValue;
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

    void sll(int regNum, int shiftAmount) {
        if (regNum >= 0 && regNum < registers.size()) {
            registers[regNum] <<= shiftAmount;
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

    void srl(int regNum, int shiftAmount) {
        if (regNum >= 0 && regNum < registers.size()) {
            registers[regNum] >>= shiftAmount;
        } else {
            std::cerr << "Error: Invalid register number.\n";
        }
    }

    bool beq(int regNum1, int regNum2, int branchAddress) {
        if (registers[regNum1] == registers[regNum2]) {
            std::cout << "Branching to address: " << branchAddress << std::endl;
            return true;
        }
        return false;
    }

    bool bne(int regNum1, int regNum2, int branchAddress) {
        if (registers[regNum1] != registers[regNum2]) {
            std::cout << "Branching to address: " << branchAddress << std::endl;
            return true;
        }
        return false;
    }

    void j(int address) {
        std::cout << "Jumping to address: " << address << std::endl;
    }

    void jr(int regNum) {
        std::cout << "Jumping to address in Register " << regNum << ": " << registers[regNum] << std::endl;
    }

    void jal(int address) {
        std::cout << "Jumping to address: " << address << " and saving return address." << std::endl;
    }

    void displayRegisters() {
        for (int i = 0; i < registers.size(); ++i) {
            std::cout << "Register " << i << ": " << registers[i] << std::endl;
        }
    }
};