#pragma once
#include <vector>
#include <cstdint>
#include <fstream>
#include <string>

using std::vector;
using std::ofstream;
using std::string;

class DataMemory {
public:
    DataMemory(); // Default Constructor
    int16_t getData(const int16_t &address);
    void writeDataToMemory(const int16_t &address, const int16_t &writeData, bool we_dm);
    void openDataOutputFile(string fileName);
    void dumpDataToFile();
private:
    vector<int16_t> data;
    ofstream outputFile;
};