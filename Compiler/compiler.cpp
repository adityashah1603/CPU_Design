#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>
using namespace std;

/*
 Instruction format notes
 R-type:
     instruction rd rs
        ex: add 2 3
            this instruction adds registers 2 and 3 together and saves the
            value in register 2.
    Special case: sll and srl
        ex: sll 2 6
            This instruction shifts the contents of register 2 by 6 bits. The
            shift ammount is saved in the rs operand slot
 I-Type:
    instruction rd imm
        ex: addi 2 23
            This instruction adds 23 to the value in register 2
    Special Case: sw, lw.
        ex: sw 2 3 8
            This instruction saves the content in register 2 to the memory
            address saved in register 3 plus the offset which is 8. This offset
            is saved in the last four bits of the instruction.
 j-type:
    instruction addr
        ex: j 3004
        addr can be up to 12 bits long
 */

unordered_map<string, string> op_code_mapping = {
    {"add", "0000"},
    {"sub", "0000"},
    {"or", "0000"},
    {"and", "0000"},
    {"not", "0000"},
    {"xor", "0000"},
    {"mult", "0000"},
    {"div", "0000"},
    {"slt", "0000"},
    {"sgt", "0000"},
    {"seq", "0000"},
    {"sll", "0000"},
    {"srl", "0000"},
    {"sw", "0001"},
    {"lw", "0010"},
    {"j", "0011"},
    {"jr", "0100"},
    {"jal", "0101"},
    {"lui", "0110"},
    {"addi", "0111"},
    {"bis", "1000"},
    {"bns", "1001"},
    {"li", "1011"},
    {"mflo", "1100"},
    {"mfhi", "1101"}
};

unordered_map<string, string> type_mapping = {
    {"add", "r"},
    {"sub", "r"},
    {"or", "r"},
    {"and", "r"},
    {"not", "r"},
    {"xor", "r"},
    {"mult", "r"},
    {"div", "r"},
    {"slt", "r"},
    {"sgt", "r"},
    {"seq", "r"},
    {"sll", "r"}, //special
    {"srl", "r"}, //special
    {"sw", "m"}, //special
    {"lw", "m"}, //special
    {"j", "j"},
    {"jr", "jr"}, //special
    {"jal", "j"},
    {"lui", "i"},
    {"addi", "i"},
    {"bis", "i"},
    {"bns", "i"},
    {"li", "i"},
    {"mflo", "r"}, //special
    {"mfhi", "r"} //special
};


unordered_map<string, string> func_code_mapping = {
        {"add", "0000"},
        {"sub", "0001"},
        {"or", "0010"},
        {"and", "0011"},
        {"not", "0100"},
        {"xor", "0101"},
        {"mult", "0110"},
        {"div", "0111"},
        {"slt", "1000"},
        {"sgt", "1001"},
        {"seq", "1010"},
        {"sll", "1011"},
        {"srl", "1100"}
    };

void saveToFile(const std::vector<std::string>& strings, const std::string& filename) {
    // Open the output file stream
    std::ofstream outfile(filename);

    // Check if the file was opened successfully
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << " for writing." << std::endl;
        return;
    }

    // Write each string to a separate line in the file
    for (const auto& str : strings) {
        outfile << str << std::endl;
    }

    // Close the file stream
    outfile.close();
}

int compile() {
    // Input file name
    std::string filename;
    std::cout << "Enter the name of the text file: ";
    std::cin >> filename;

    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }
    // 2D array to store words
    std::vector<std::vector<std::string>> instructions;
    std::vector<std::string> binary;


    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::vector<std::string> words;
        std::stringstream ss(line);
        std::string word;

        // Split the line into words
        while (ss >> word) {
            words.push_back(word);
        }

        // Add the words of this line to the 2D array
        instructions.push_back(words);
    }

    file.close();

    // Display the content of the 2D array
    std::cout << "\nBinary Representation:\n";
    for (const auto& row : instructions) {
        if (row.empty()) continue;

        string instr = "0000000000000000";
        string instrtype = "";
        for (size_t i = 0; i < row.size(); ++i) {
            string word = row[i];
            if (i == 0) { // Opcode
                auto opcode = op_code_mapping.find(row[i]);
                if (opcode == op_code_mapping.end()) {
                    cerr << "Error: Invalid instruction '" << row[i] << "'" << endl;
                    return 1;
                }
                instr.replace(0, 4, opcode->second);
                instrtype = type_mapping[row[i]];
                if (opcode->second == "0000") { // R-Type
                    auto func = func_code_mapping.find(row[i]);
                    if (func != func_code_mapping.end()) {
                        instr.replace(12, 4, func->second);
                    }
                }
            } else { // Operands
                int number = stoi(row[i]);
                if (instrtype == "i" && i == 2) {
                    std::bitset<8> b(number); // Convert to 4-bit binary
                    instr.replace(i*4, 8, b.to_string());
                }
                else if (instrtype == "j" && i == 1) {
                    std::bitset<12> b(number); // Convert to 4-bit binary
                    instr.replace(i*4, 12, b.to_string());
                }
                else {
                    std::bitset<4> b(number); // Convert to 4-bit binary
                    instr.replace(i*4, 4, b.to_string());
                }
            }
        }
        binary.push_back(instr);
    }
 
    std::cout << "Enter the name of the output file: ";
    std::cin >> filename;
    saveToFile(binary, filename);
    
    return 0;
}
