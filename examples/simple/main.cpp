#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Core6502.hpp"


int main(int argc, char ** argv) {

	// Create memory
	uint8_t mem[0xFFFF];
	
	// Create CPU
	Core6502::CPU cpu(mem);

	// Create test values
    uint8_t opCode = 0x2D;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteLB = 0xFE;
    uint8_t absoluteUB = 0xCA;
    uint16_t addr = absoluteLB + (absoluteUB << 8);
    uint8_t aTestVal = 0xFF;
    uint8_t mask = 0x0F;

    // Set Registers and memory
    cpu.registers.PC = pcVal;
    cpu.mem[pcVal] = absoluteLB;
    cpu.mem[pcVal+1] = absoluteUB;
    cpu.mem[addr] = mask;
    cpu.registers.A = aTestVal;

   
    // Perform instruction
    cpu.instructions[opCode].instructionFunction(cpu, cpu.instructions[opCode]);
	std::cout << "Zero: " << (uint16_t)cpu.status.ZeroFlag << std::endl;
	

	return 0;

}
