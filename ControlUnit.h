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
    bool RegDst;
    bool ALUSrc;
    bool MemToReg;
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool Branch;
    bool Jump;
    ALUOperations AluOp;
};

class ControlUnit {
public:
    void setOpcode(uint8_t opcode);
    void setFunct(uint8_t funct);
    ControlSignals generateControls();
private:
    uint8_t opcode;
    uint8_t funct;
    ControlSignals control;
};