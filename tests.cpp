#include <cassert>
#include <iostream>
#include <string>
#include "main.cpp"
using namespace std;

int main() {
    auto instructions = loadInstructions("Operands.csv");

    // MUL
    string MUL = "10011011000100110111110110001000";
    assert(disassemble(MUL, instructions) == "MUL X8, X12, X19");
    cout << "MUL passed" << endl;

    // DDI
    string ADDI = "10010001000000000000010010100000";
    assert(disassemble(ADDI, instructions) == "ADDI X0, X5, #1");
    cout << "ADDI passed" << endl;

    // LSR
    string LSR = "11010011010000011111110010100100";
    assert(disassemble(LSR, instructions) == "LSR X4, X5, X1");
    cout << "LSR passed" << endl;
    return 0;
}