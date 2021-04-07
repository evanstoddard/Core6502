#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Core6502.hpp"

void MyInstruction(Core6502::CPU &cpu, Core6502::Instruction & instruction) {
	std::cout << "Inside user defined instruction..." << std::endl;
	std::cout << "Address of CPU from instruction: " << std::hex << &cpu << std::endl;
	std::cout << "Address of Instruction from instruction: " << std::hex << &instruction << std::endl;
}

int main(int argc, char ** argv) {

	// Create memory
	uint8_t mem[0xFFFF];
	
	// Set reset vector to 0xBEEF
	mem[0xFFFC] = 0xEF;
	mem[0xFFFD] = 0xBE;

	// Create CPU instance
	Core6502::CPU cpu(mem);

	// Reset CPU
	cpu.reset();

	// Print out program counter
	std::cout << "CPU Program Counter: 0x" << cpu.registers.PC << std::endl;
	
	cpu.instructions[0xFF] = (Core6502::Instruction){false, 0xFF, 2, MyInstruction};

	std::cout << "Address of CPU from Main: " << std::hex << &cpu << std::endl;
	std::cout << "Address of Instruction from Main: " << std::hex << &cpu.instructions[0xFF] << std::endl;
	std::cout << std::endl;

	// Call instruction
	std::cout << "Calling newly defined instruction...\n" << std::endl;
	cpu.instructions[0xFF].instructionFunction(cpu, cpu.instructions[0xFF]);

	return 0;

}
