#include <fstream>
#include <cstdint>

using std::ifstream;

class InstructionMemory {

public:
    InstructionMemory(const char* filename) { InstructionFile.open(filename); }
    uint16_t getInstruction(const uint16_t &address);
private:
    ifstream InstructionFile;
};