#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
using namespace std;

struct Instruction {
    string mnemonic;
    string format;
    int width;
};

unordered_map<string, Instruction> loadInstructions(const string& filename) {
    unordered_map<string, Instruction> instructions;
    
    ifstream file(filename);
    string line;
    
    // skip header
    getline(file, line);
    
    while (getline(file, line)) {
        stringstream ss(line);
        string mnemonic, format, width, binary;
        
        getline(ss, mnemonic, ',');
        getline(ss, format, ',');
        getline(ss, width, ',');
        getline(ss, binary, ',');
        
        instructions[binary] = {mnemonic, format, stoi(width)};
    }
    
    return instructions;
}

string disassemble(const string& bin, const unordered_map<string, Instruction>& instructions) {
    // try every exact width
    for (const auto& [opcode, instr] : instructions) {
        if (bin.substr(0, instr.width) == opcode) {
            string fmt = instr.format;
            string mnemonic = instr.mnemonic;

            try {
                if (fmt == "R") {
                    int Rd = stoi(bin.substr(27, 5), nullptr, 2);
                    int Rn = stoi(bin.substr(22, 5), nullptr, 2);
                    int Rm = stoi(bin.substr(11, 5), nullptr, 2);
                    return mnemonic + " X" + to_string(Rd) + ", X" + to_string(Rn) + ", X" + to_string(Rm);
                } else if (fmt == "I") {
                    int Rd = stoi(bin.substr(27, 5), nullptr, 2);
                    int Rn = stoi(bin.substr(22, 5), nullptr, 2);
                    int imm = stoi(bin.substr(10, 12), nullptr, 2);
                    return mnemonic + " X" + to_string(Rd) + ", X" + to_string(Rn) + ", #" + to_string(imm);
                } else if (fmt == "D") {
                    int Rt = stoi(bin.substr(27, 5), nullptr, 2);
                    int Rn = stoi(bin.substr(20, 5), nullptr, 2);
                    int addr = stoi(bin.substr(11, 9), nullptr, 2);
                    return mnemonic + " X" + to_string(Rt) + ", [X" + to_string(Rn) + ", #" + to_string(addr) + "]";
                } else if (fmt == "B") {
                    int addr = stoi(bin.substr(6, 26), nullptr, 2);
                    return mnemonic + " " + to_string(addr << 2);
                } else if (fmt == "CB") {
                    int Rt = stoi(bin.substr(27, 5), nullptr, 2);
                    int addr = stoi(bin.substr(8, 19), nullptr, 2);
                    return mnemonic + " X" + to_string(Rt) + ", " + to_string(addr << 2);
                } else if (fmt == "IM") {
                    int Rd = stoi(bin.substr(27, 5), nullptr, 2);
                    int imm = stoi(bin.substr(9, 16), nullptr, 2);
                    return mnemonic + " X" + to_string(Rd) + ", #" + to_string(imm);
                }
            } catch (...) {
                return "invalid format for " + mnemonic;
            }
        }
    }
    return "idk...";
}
int main() {
    auto instructions = loadInstructions("Operands.csv");
    
    string input;
    while (true) {
        cout << "32 bit binary instruction: ";
        cin >> input;

        if (input.size() != 32) {
            cerr << "has to be 32 bits" << endl;
            continue;
        }

        cout << "Assembly: " << disassemble(input, instructions) << endl;
    }
    return 0;
}

