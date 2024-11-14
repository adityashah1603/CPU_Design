#pragma once

#include <cstdint>

typedef enum {
    ALU_ADD,
    ALU_SUB,
    ALU_OR,
    ALU_AND,
    ALU_NOT,
    ALU_XOR,
    ALU_MULT,
    ALU_DIV,
    ALU_SLT,
    ALU_SGT,
    ALU_SLL,
    SLU_SRL
} ALUOperations;

struct ControlSignals{
    bool RegDst = false;
    bool ALUSrc = false;
    bool MemToReg = false;
    bool RegWrite = false;
    bool MemRead = false;
    bool MemWrite = false;
    bool Branch = false;
    bool Jump = false;
    ALUOperations AluOp = ALU_ADD;
};

class ControlUnit {
public:
    void setOpcode(uint8_t inputOpcode);
    void setFunct(uint8_t inputFunct);
    ControlSignals generateControls();
private:
    uint8_t opcode;
    uint8_t funct;
    ControlSignals control;

    void clearControlSignals();
};