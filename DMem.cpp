#include <iostream>
#include "DMem.h"

using std::endl;

DataMemory::DataMemory() {
    data.resize(32000);
}

int16_t DataMemory::getData(const int16_t &address) {
    int16_t returnData {0};
    if(address < 32000) {
        returnData = data[address];
    }
    return returnData;
}

void DataMemory::writeDataToMemory(const int16_t &address, const int16_t &writeData, bool we_dm) {
    if(we_dm) {
        data[address] = writeData;
    }
    else { return; }
        
}

void DataMemory::openDataOutputFile(string fileName) {
    outputFile.open(fileName);
}

void DataMemory::dumpDataToFile() {
    if(!outputFile.is_open()) {
        return;
    }
    for(int i {0}; i < data.size(); i++) {
        outputFile << i << ": " << data[i] << endl;
    }
}
