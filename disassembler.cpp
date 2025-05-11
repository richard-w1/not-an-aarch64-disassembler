#include <iostream>
#include "main.cpp"
using namespace std;

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