//
//  Core6502.cpp
//  Core6502
//
//  Created by Evan Stoddard on 3/30/21.
//

#include "Core6502.hpp"
#include <iostream>

Core6502::CPU::CPU() {
    // Create memory
    mem = new uint8_t[0xFFFF];

    // Setup instruction map
    setupInstructionMap();
}

Core6502::CPU::CPU(uint8_t * memPtr) {
    
    // Set memory location
    mem = memPtr;
    
    // Setup instruction map
    setupInstructionMap();

}

uint8_t Core6502::CPU::fetchByte() {

    // Grab value from memory at PC index and increment PC
    uint8_t value = mem[registers.PC];
    registers.PC++;

    return value;

}

void Core6502::CPU::setupInstructionMap() {
    
    // LDA Instructions
    instructions[0xA9] = (Core6502::Instruction){false, 0xA9, 2, Core6502::LDA_Immediate};
    instructions[0xA5] = (Core6502::Instruction){false, 0xA5, 2, Core6502::LDA_Zero_Page};
    instructions[0xB5] = (Core6502::Instruction){false, 0xB5, 2, Core6502::LDA_Zero_Page_X};
    instructions[0xAD] = (Core6502::Instruction){false, 0xAD, 2, Core6502::LDA_Absolute};
    instructions[0xBD] = (Core6502::Instruction){false, 0xBD, 2, Core6502::LDA_Absolute_X};
    instructions[0xB9] = (Core6502::Instruction){false, 0xB9, 2, Core6502::LDA_Absolute_Y};
    instructions[0xA1] = (Core6502::Instruction){false, 0xA1, 2, Core6502::LDA_Indirect_X};
    instructions[0xB1] = (Core6502::Instruction){false, 0xB1, 2, Core6502::LDA_Indirect_Y};

}