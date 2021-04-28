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
    // Test Values
	uint8_t opCode = 0xB0;
	uint16_t pcVal = 0x4000;
    int8_t offset = 0x40;
	uint8_t flag = 0x0;

	// Set memory and flags
    cpu.registers.PC = pcVal;
	cpu.mem[pcVal] = offset;
	cpu.status.bitfield.CarryFlag = flag;

	// Perform Instruction
	cpu.instructions[opCode].instructionFunction(cpu, cpu.instructions[opCode]);

	std::cout << "Val: " << std::hex << (uint16_t)cpu.registers.PC << std::endl;
	

	return 0;

}
