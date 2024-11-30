#pragma once
#include <fstream>
#include <vector>
#include <cstdint>

using std::ofstream;
using std::vector;

class DataMemory {
public:
    DataMemory(); // Default Constructor
    DataMemory(const char* filename); // Constructor for provided Data File
    ~DataMemory() { DataFile.close(); } // Destructor
    uint16_t getData(const uint16_t &address);
    void writeDataToMemory(const uint16_t &address, const uint16_t &writeData);
private:
    ofstream DataFile;
    vector<uint16_t> data;
    bool we_dm;
};