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

void Core6502::CPU::reset() {

    // Set PC to 0xFFFC and all other registers to 0
    registers.PC    = 0xFFFC;
    registers.SP    = 0x0;
    registers.A     = 0x0;
    registers.X     = 0x0;
    registers.Y     = 0x0;

    // Set flags to a default state and disable interrupts
    status.BreakCommand = 0;
    status.CarryFlag = 0;
    status.DecimalMode = 0;
    status.InterruptDisable = 1;
    status.NegativeFlag = 0;
    status.OverflowFlag = 0;
    status.UserFlag = 0;
    status.ZeroFlag = 1;

    // Set the program counter to address at reset vector
    uint16_t effective_addr  = fetchByte() | (fetchByte() << 8);
    registers.PC = effective_addr;

}

uint8_t Core6502::CPU::fetchByte() {

    // Grab value from memory at PC index and increment PC
    uint8_t value = mem[registers.PC];
    registers.PC++;

    return value;

}

uint8_t Core6502::CPU::zeroPageAddr() {
    // Return fetched byte
    return fetchByte();
}

uint8_t Core6502::CPU::zeroPageXAddr() {
    // Fetch Offset and add value of X register
    return fetchByte() + registers.X;
}

uint8_t Core6502::CPU::zeroPageYAddr() {
    // Fetch Offset and add value of Y register
    return fetchByte() + registers.Y;
}

uint16_t Core6502::CPU::absoluteAddr() {
    // Fetch 16-bit address
    return fetchByte() + (fetchByte() << 8);
}

uint16_t Core6502::CPU::absoluteXAddr() {
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = fetchByte();
             addr += (fetchByte() << 8);
             addr += registers.X;

    return addr;
}

uint16_t Core6502::CPU::absoluteYAddr() {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr  = fetchByte();
             addr += (fetchByte() << 8);
             addr += registers.Y;

    return addr;
}
uint16_t Core6502::CPU::indirectXAddr() {
    // Fetch offset and add value in register X
    uint8_t zero_addr =  fetchByte();
            zero_addr += registers.X;
    
    // Read 16-bit address from zero page address
    uint16_t effective_addr =  mem[zero_addr];
             effective_addr += (mem[zero_addr + 1] << 8);

    return effective_addr;
}
uint16_t Core6502::CPU::indirectYAddr() {
    // Fetch 16-bit address from zero page memory
    uint8_t offset = fetchByte();
    uint16_t effective_addr =  mem[offset];
             effective_addr += (mem[offset + 1] << 8);

    // Add Y to effecting address
    effective_addr += registers.Y;

    return effective_addr;
}

void Core6502::CPU::setupInstructionMap() {
    
    // LDA Instructions
    instructions[0xA9] = (Core6502::Instruction){false, 0xA9, 2, Core6502::LDA_Immediate};
    instructions[0xA5] = (Core6502::Instruction){false, 0xA5, 3, Core6502::LDA_Zero_Page};
    instructions[0xB5] = (Core6502::Instruction){false, 0xB5, 4, Core6502::LDA_Zero_Page_X};
    instructions[0xAD] = (Core6502::Instruction){false, 0xAD, 4, Core6502::LDA_Absolute};
    instructions[0xBD] = (Core6502::Instruction){false, 0xBD, 4, Core6502::LDA_Absolute_X};
    instructions[0xB9] = (Core6502::Instruction){false, 0xB9, 4, Core6502::LDA_Absolute_Y};
    instructions[0xA1] = (Core6502::Instruction){false, 0xA1, 6, Core6502::LDA_Indirect_X};
    instructions[0xB1] = (Core6502::Instruction){false, 0xB1, 5, Core6502::LDA_Indirect_Y};

    // LDX Instructions
    instructions[0xA2] = (Core6502::Instruction){false, 0xA2, 2, Core6502::LDX_Immediate};
    instructions[0xA6] = (Core6502::Instruction){false, 0xA6, 3, Core6502::LDX_Zero_Page};
    instructions[0xB6] = (Core6502::Instruction){false, 0xB6, 4, Core6502::LDX_Zero_Page_Y};
    instructions[0xAE] = (Core6502::Instruction){false, 0xAE, 4, Core6502::LDX_Absolute};
    instructions[0xBE] = (Core6502::Instruction){false, 0xBE, 4, Core6502::LDX_Absolute_Y};

    // LDY Instructions
    instructions[0xA0] = (Core6502::Instruction){false, 0xA0, 2, Core6502::LDY_Immediate};
    instructions[0xA4] = (Core6502::Instruction){false, 0xA4, 3, Core6502::LDY_Zero_Page};
    instructions[0xB4] = (Core6502::Instruction){false, 0xB4, 4, Core6502::LDY_Zero_Page_X};
    instructions[0xAC] = (Core6502::Instruction){false, 0xAC, 4, Core6502::LDY_Absolute};
    instructions[0xBC] = (Core6502::Instruction){false, 0xBC, 4, Core6502::LDY_Absolute_X};

    // STA Instructions
    instructions[0x85] = (Core6502::Instruction){false, 0x85, 3, Core6502::STA_Zero_Page};
    instructions[0x95] = (Core6502::Instruction){false, 0x95, 4, Core6502::STA_Zero_Page_X};
    instructions[0x8D] = (Core6502::Instruction){false, 0x8D, 4, Core6502::STA_Absolute};
    instructions[0x9D] = (Core6502::Instruction){false, 0x9D, 5, Core6502::STA_Absolute_X};
    instructions[0x99] = (Core6502::Instruction){false, 0x99, 5, Core6502::STA_Absolute_Y};
    instructions[0x81] = (Core6502::Instruction){false, 0x81, 6, Core6502::STA_Indirect_X};
    instructions[0x91] = (Core6502::Instruction){false, 0x91, 6, Core6502::STA_Indirect_Y};

    // STX Instructions
    instructions[0x86] = (Core6502::Instruction){false, 0x86, 3, Core6502::STX_Zero_Page};
    instructions[0x96] = (Core6502::Instruction){false, 0x96, 4, Core6502::STX_Zero_Page_Y};
    instructions[0x8E] = (Core6502::Instruction){false, 0x8E, 4, Core6502::STX_Absolute};
    
    // STY Instructions
    instructions[0x84] = (Core6502::Instruction){false, 0x84, 3, Core6502::STY_Zero_Page};
    instructions[0x94] = (Core6502::Instruction){false, 0x94, 4, Core6502::STY_Zero_Page_X};
    instructions[0x8C] = (Core6502::Instruction){false, 0x8C, 4, Core6502::STY_Absolute};

    // AND Instructions
    instructions[0x29] = (Core6502::Instruction){false, 0x29, 2, Core6502::AND_Immediate};
    instructions[0x25] = (Core6502::Instruction){false, 0x25, 3, Core6502::AND_Zero_Page};
    instructions[0x35] = (Core6502::Instruction){false, 0x35, 4, Core6502::AND_Zero_Page_X};
    instructions[0x2D] = (Core6502::Instruction){false, 0x2D, 4, Core6502::AND_Absolute};
    instructions[0x3D] = (Core6502::Instruction){false, 0x3D, 4, Core6502::AND_Absolute_X};
    instructions[0x39] = (Core6502::Instruction){false, 0x39, 4, Core6502::AND_Absolute_Y};
    instructions[0x21] = (Core6502::Instruction){false, 0x21, 6, Core6502::AND_Indirect_X};
    instructions[0x31] = (Core6502::Instruction){false, 0x31, 5, Core6502::AND_Indirect_Y};

    // OR Instructions
    instructions[0x09] = (Core6502::Instruction){false, 0x09, 2, Core6502::ORA_Immediate};
    instructions[0x05] = (Core6502::Instruction){false, 0x05, 3, Core6502::ORA_Zero_Page};
    instructions[0x15] = (Core6502::Instruction){false, 0x15, 4, Core6502::ORA_Zero_Page_X};
    instructions[0x0D] = (Core6502::Instruction){false, 0x0D, 4, Core6502::ORA_Absolute};
    instructions[0x1D] = (Core6502::Instruction){false, 0x1D, 4, Core6502::ORA_Absolute_X};
    instructions[0x19] = (Core6502::Instruction){false, 0x19, 4, Core6502::ORA_Absolute_Y};
    instructions[0x01] = (Core6502::Instruction){false, 0x01, 6, Core6502::ORA_Indirect_X};
    instructions[0x11] = (Core6502::Instruction){false, 0x11, 5, Core6502::ORA_Indirect_Y};

    // EOR Instructions
    instructions[0x49] = (Core6502::Instruction){false, 0x49, 2, Core6502::EOR_Immediate};
    instructions[0x45] = (Core6502::Instruction){false, 0x45, 3, Core6502::EOR_Zero_Page};
    instructions[0x55] = (Core6502::Instruction){false, 0x55, 4, Core6502::EOR_Zero_Page_X};
    instructions[0x4D] = (Core6502::Instruction){false, 0x4D, 4, Core6502::EOR_Absolute};
    instructions[0x5D] = (Core6502::Instruction){false, 0x5D, 4, Core6502::EOR_Absolute_X};
    instructions[0x59] = (Core6502::Instruction){false, 0x59, 4, Core6502::EOR_Absolute_Y};
    instructions[0x41] = (Core6502::Instruction){false, 0x41, 6, Core6502::EOR_Indirect_X};
    instructions[0x51] = (Core6502::Instruction){false, 0x51, 5, Core6502::EOR_Indirect_Y};

    // BIT Instructions
    instructions[0x24] = (Core6502::Instruction){false, 0x24, 3, Core6502::BIT_Zero_Page};
    instructions[0x2C] = (Core6502::Instruction){false, 0x2C, 4, Core6502::BIT_Absolute};

    // INC Instructions
    instructions[0xE6] = (Core6502::Instruction){false, 0xE6, 5, Core6502::INC_Zero_Page};
    instructions[0xF6] = (Core6502::Instruction){false, 0xF6, 6, Core6502::INC_Zero_Page_X};
    instructions[0xEE] = (Core6502::Instruction){false, 0xEE, 6, Core6502::INC_Absolute};
    instructions[0xFE] = (Core6502::Instruction){false, 0xFE, 7, Core6502::INC_Absolute_X};

    // Transfer Instructions
    instructions[0xAA] = (Core6502::Instruction){false, 0xAA, 2, Core6502::TAX};
    instructions[0xA8] = (Core6502::Instruction){false, 0xA8, 2, Core6502::TAY};
    instructions[0x8A] = (Core6502::Instruction){false, 0x8A, 2, Core6502::TXA};
    instructions[0x98] = (Core6502::Instruction){false, 0x98, 2, Core6502::TYA};

    // Status Flag Instructions
    instructions[0x18] = (Core6502::Instruction){false, 0x18, 2, Core6502::CLC};
    instructions[0xD8] = (Core6502::Instruction){false, 0xD8, 2, Core6502::CLD};
    instructions[0x58] = (Core6502::Instruction){false, 0x58, 2, Core6502::CLI};
    instructions[0xB8] = (Core6502::Instruction){false, 0xB8, 2, Core6502::CLV};
    instructions[0x38] = (Core6502::Instruction){false, 0x38, 2, Core6502::SEC};
    instructions[0xF8] = (Core6502::Instruction){false, 0xF8, 2, Core6502::SED};
    instructions[0x78] = (Core6502::Instruction){false, 0x78, 2, Core6502::SEI};

}