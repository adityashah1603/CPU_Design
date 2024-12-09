//
//  ALU.cpp
//  ALU
//
//  Created by Peter Xiong on 10/21/24.
//

#include <cstdint>
#include <limits>
#include<iostream>
#include "ALU.h"
using std::cerr;
using std::endl;


void ALU::compute(ALUOperations func, int16_t &op1, int16_t op2, int16_t& result, bool& overflow, bool &zero, int16_t hi) {
    overflow = 0;
    int32_t result32;
    switch (func) {
        case 0: // add
            result = op1+op2;
            if (op2 > 0 && op1 > (std::numeric_limits<int16_t>::max() - op2)) {
                overflow = 1; // Positive overflow
            }
            if (op2 < 0 && op1 < (std::numeric_limits<int16_t>::min() - op2)) {
                overflow = 1; // Negative overflow
            }
            break;
        case 1: // subtract
            result = op1-op2;
            if ((op2 > 0 && op1 < std::numeric_limits<int16_t>::min() + op2) || (op2 < 0 && op1 > std::numeric_limits<int16_t>::max() + op2)) {
                    overflow = 1;
                    }
            break;
        case 2: // or
            result = op1 | op2;
            break;
        case 3: // and
            result = op1 & op2;
            break;
        case 4: // not
            result = ~op2;
            break;
        case 5: // xor
            result = op1 ^ op2;
            break;
        case 6: // mult
            result32 = (int32_t)op1 * (int32_t)op2;
            result = (int16_t)result32;
            hi = (int16_t)(result32>>16);
            overflow = 0;
            break;
        case 7: // div
            if (op2==0)
            {
                cerr<< "Division by zero"<<endl;
                result = 0;
                overflow = 1;
            }
            else{            
            result = op1 / op2;
            hi = op1 % op2;
            overflow = 0;}
            break;
        case 8: // slt
            result = op1 < op2;
            overflow = 0;
            break;
        case 9: // sgt
            result = op1 > op2;
            overflow = 0;
            break;
        case 10: // seq
            result = op1 == op2;
            overflow = 0;
            break;
        case 11: // sll
            result = op1 << (op2 & 0xF);
            overflow = 0;
            break;
        case 12: // srl
            result = op1 >> (op2 & 0xF);
            overflow = 0;
            break;
        default:
            std::cerr << "Error: Invalid ALU function code: " << func << std::endl;
            result = 0;
            overflow = 0;
            zero = true;
            break;
    }
    zero = !result;
   
}