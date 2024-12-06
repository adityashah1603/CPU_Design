#pragma once
#ifndef ALU_H
#define ALU_H
#include <cstdint>

typedef enum{
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
    ALU_SRL
} ALUOperation;

class ALU {
private:
   
public:
    void compute(ALUOperation func,  int16_t &op1, int16_t op2, int16_t& result, bool& overflow, bool &zero);
};
#endif