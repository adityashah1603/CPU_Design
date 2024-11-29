#pragma once

#include <cstdint>

class ALU {
private:
   
public:
    void compute(int func, int16_t &op1, int16_t op2, int16_t& result, bool& overflow, bool &zero);
};