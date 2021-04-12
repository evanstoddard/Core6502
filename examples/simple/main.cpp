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
    uint8_t opCode = 0xC6;
    uint16_t pcVal = 0x4000;
    uint8_t absoluteUB = 0xCA;
    uint8_t absoluteLB = 0xFE;
	uint8_t xVal = 0x10;
    uint16_t addr = 0xFF;
    uint8_t testVal = 0x0F;

    // Set Registers and memory
    cpu.registers.PC = pcVal;
	cpu.registers.X = xVal;
    cpu.mem[addr] = testVal;
    //cpu.mem[pcVal+1] = absoluteUB;
    //cpu.mem[addr + xVal] = testVal;
   
    // Perform instruction
    cpu.instructions[opCode].instructionFunction(cpu, cpu.instructions[opCode]);
	std::cout << "Val: " << (uint16_t)cpu.mem[addr] << std::endl;
	

	return 0;

}
