#pragma once
#include <fstream>
#include <vector>
#include <cstdint>

using std::ofstream;
using std::vector;

class DataMemory {
public:
    DataMemory(const char* filename) { DataFile.open(filename); };
    ~DataMemory();
    uint16_t getData(const uint16_t &address);

private:
    ofstream DataFile;
    vector<uint16_t> 
}