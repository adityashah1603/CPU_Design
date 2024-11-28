#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

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
        {"lui", "1010"}
    };

int main() {
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
    std::vector<std::vector<std::string>> binary;


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
    std::cout << "\nWords stored in the 2D array:\n";
    for (const auto& row : instructions) {
        int iteration = 0;
        string binary = "0000000000000000";
        for (const auto& word : row) {
            if (iteration == 0) // instruction name = op code
                binary.replace(0, 4, op_code_mapping[word]);
            else {
                binary.replace(0, 4, op_code_mapping[word]);
            }
            //std::cout << word << " ";
            iteration++;
        }
        std::cout << std::endl;
    }

    return 0;
}
