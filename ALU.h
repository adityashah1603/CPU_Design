#pragma once
#ifndef ALU_H
#define ALU_H
#include <cstdint>
#include "ControlUnit.h"

class ALU {
private:
   
public:
    void compute(ALUOperations func,  int16_t &op1, int16_t op2, int16_t& result, bool& overflow, bool &zero);
};
#endif