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

uint8_t Core6502::CPU::fetchFromMemory(Core6502::Instruction &instruction) {

    // Perform addressing operation
    if (instruction.addressFunction != Core6502::CPU::immediate)
        return mem[instruction.addressFunction(*this)];
    else
        return instruction.addressFunction(*this);

}

uint16_t Core6502::CPU::immediate(Core6502::CPU &cpu) {
    return cpu.fetchByte();
}
uint16_t Core6502::CPU::zeroPageAddr(Core6502::CPU &cpu) {
    // Return fetched byte
    return cpu.fetchByte();
}
uint16_t Core6502::CPU::zeroPageXAddr(Core6502::CPU &cpu) {
    // Fetch Offset and add value of X register
    return (uint8_t)(cpu.fetchByte() + cpu.registers.X);
}
uint16_t Core6502::CPU::zeroPageYAddr(Core6502::CPU &cpu) {
    // Fetch Offset and add value of Y register
    return (uint8_t)(cpu.fetchByte() + cpu.registers.Y);
}
uint16_t Core6502::CPU::absoluteAddr(Core6502::CPU &cpu) {
    // Fetch 16-bit address
    return cpu.fetchByte() + (cpu.fetchByte() << 8);
}
uint16_t Core6502::CPU::absoluteXAddr(Core6502::CPU &cpu) {
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.X;

    return addr;
}
uint16_t Core6502::CPU::absoluteYAddr(Core6502::CPU &cpu) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.Y;

    return addr;
}
uint16_t Core6502::CPU::indirectXAddr(Core6502::CPU &cpu) {
    // Fetch offset and add value in register X
    uint8_t zero_addr =  cpu.fetchByte();
            zero_addr += cpu.registers.X;
    
    // Read 16-bit address from zero page address
    uint16_t effective_addr =  cpu.mem[zero_addr];
             effective_addr += (cpu.mem[zero_addr + 1] << 8);

    return effective_addr;
}
uint16_t Core6502::CPU::indirectYAddr(Core6502::CPU &cpu) {
    // Fetch 16-bit address from zero page memory
    uint8_t offset = cpu.fetchByte();
    uint16_t effective_addr =  cpu.mem[offset];
             effective_addr += (cpu.mem[offset + 1] << 8);

    // Add Y to effecting address
    effective_addr += cpu.registers.Y;

    return effective_addr;
}
uint16_t Core6502::CPU::indirectAddr(Core6502::CPU &cpu) {
    // Fetch 16-bit address from address specified by passed in address
    // Note.  This implementation contains the page boundary bug in the
    // Original 6502.  See http://obelisk.me.uk/6502/reference.html#JMP
    // for details.
    uint8_t LB = cpu.fetchByte();
    uint8_t UB = cpu.fetchByte();

    // Get final address
    uint16_t memAddr =  LB + (UB << 8);
    
    uint16_t effectiveAddr =  cpu.mem[memAddr];
    
    // Implement page boundary bug
    if (LB == 0xFF) effectiveAddr += (cpu.mem[(memAddr & 0xFF00)] << 8);    
    else effectiveAddr += (cpu.mem[memAddr + 1] << 8);
             

    return effectiveAddr;

}
uint16_t Core6502::CPU::relativeAddr(Core6502::CPU &cpu) {
    // Fetch signed byte and add to PC
    int8_t offset = cpu.fetchByte();
    
    uint16_t addr = cpu.registers.PC + offset;

    return addr;
    
}

void Core6502::CPU::setupInstructionMap() {
    
    // LDA Instructions
    instructions[0xA9] = (Core6502::Instruction){0xA9, 2, Core6502::LDA, Core6502::CPU::immediate};
    instructions[0xA5] = (Core6502::Instruction){0xA5, 3, Core6502::LDA, Core6502::CPU::zeroPageAddr};
    instructions[0xB5] = (Core6502::Instruction){0xB5, 4, Core6502::LDA, Core6502::CPU::zeroPageXAddr};
    instructions[0xAD] = (Core6502::Instruction){0xAD, 4, Core6502::LDA, Core6502::CPU::absoluteAddr};
    instructions[0xBD] = (Core6502::Instruction){0xBD, 4, Core6502::LDA, Core6502::CPU::absoluteXAddr};
    instructions[0xB9] = (Core6502::Instruction){0xB9, 4, Core6502::LDA, Core6502::CPU::absoluteYAddr};
    instructions[0xA1] = (Core6502::Instruction){0xA1, 6, Core6502::LDA, Core6502::CPU::indirectXAddr};
    instructions[0xB1] = (Core6502::Instruction){0xB1, 5, Core6502::LDA, Core6502::CPU::indirectYAddr};

    // LDX Instructions
    instructions[0xA2] = (Core6502::Instruction){0xA2, 2, Core6502::LDX, Core6502::CPU::immediate};
    instructions[0xA6] = (Core6502::Instruction){0xA6, 3, Core6502::LDX, Core6502::CPU::zeroPageAddr};
    instructions[0xB6] = (Core6502::Instruction){0xB6, 4, Core6502::LDX, Core6502::CPU::zeroPageYAddr};
    instructions[0xAE] = (Core6502::Instruction){0xAE, 4, Core6502::LDX, Core6502::CPU::absoluteAddr};
    instructions[0xBE] = (Core6502::Instruction){0xBE, 4, Core6502::LDX, Core6502::CPU::absoluteYAddr};

    // LDY Instructions
    instructions[0xA0] = (Core6502::Instruction){0xA0, 2, Core6502::LDY , Core6502::CPU::immediate};
    instructions[0xA4] = (Core6502::Instruction){0xA4, 3, Core6502::LDY , Core6502::CPU::zeroPageAddr};
    instructions[0xB4] = (Core6502::Instruction){0xB4, 4, Core6502::LDY , Core6502::CPU::zeroPageXAddr};
    instructions[0xAC] = (Core6502::Instruction){0xAC, 4, Core6502::LDY , Core6502::CPU::absoluteAddr};
    instructions[0xBC] = (Core6502::Instruction){0xBC, 4, Core6502::LDY , Core6502::CPU::absoluteXAddr};

    // STA Instructions
     instructions[0x85] = (Core6502::Instruction){0x85, 3, Core6502::STA, Core6502::CPU::zeroPageAddr};
     instructions[0x95] = (Core6502::Instruction){0x95, 4, Core6502::STA, Core6502::CPU::zeroPageXAddr};
     instructions[0x8D] = (Core6502::Instruction){0x8D, 4, Core6502::STA, Core6502::CPU::absoluteAddr};
     instructions[0x9D] = (Core6502::Instruction){0x9D, 5, Core6502::STA, Core6502::CPU::absoluteXAddr};
     instructions[0x99] = (Core6502::Instruction){0x99, 5, Core6502::STA, Core6502::CPU::absoluteYAddr};
     instructions[0x81] = (Core6502::Instruction){0x81, 6, Core6502::STA, Core6502::CPU::indirectXAddr};
     instructions[0x91] = (Core6502::Instruction){0x91, 6, Core6502::STA, Core6502::CPU::indirectYAddr};

    // STX Instructions
    instructions[0x86] = (Core6502::Instruction){0x86, 3, Core6502::STX, Core6502::CPU::zeroPageAddr};
    instructions[0x96] = (Core6502::Instruction){0x96, 4, Core6502::STX, Core6502::CPU::zeroPageYAddr};
    instructions[0x8E] = (Core6502::Instruction){0x8E, 4, Core6502::STX, Core6502::CPU::absoluteAddr};
     
    // STY Instructions
    instructions[0x84] = (Core6502::Instruction){0x84, 3, Core6502::STY, Core6502::CPU::zeroPageAddr};
    instructions[0x94] = (Core6502::Instruction){0x94, 4, Core6502::STY, Core6502::CPU::zeroPageXAddr};
    instructions[0x8C] = (Core6502::Instruction){0x8C, 4, Core6502::STY, Core6502::CPU::absoluteAddr};

    // AND Instructions
    instructions[0x29] = (Core6502::Instruction){0x29, 2, Core6502::AND, Core6502::CPU::immediate};
    instructions[0x25] = (Core6502::Instruction){0x25, 3, Core6502::AND, Core6502::CPU::zeroPageAddr};
    instructions[0x35] = (Core6502::Instruction){0x35, 4, Core6502::AND, Core6502::CPU::zeroPageXAddr};
    instructions[0x2D] = (Core6502::Instruction){0x2D, 4, Core6502::AND, Core6502::CPU::absoluteAddr};
    instructions[0x3D] = (Core6502::Instruction){0x3D, 4, Core6502::AND, Core6502::CPU::absoluteXAddr};
    instructions[0x39] = (Core6502::Instruction){0x39, 4, Core6502::AND, Core6502::CPU::absoluteYAddr};
    instructions[0x21] = (Core6502::Instruction){0x21, 6, Core6502::AND, Core6502::CPU::indirectXAddr};
    instructions[0x31] = (Core6502::Instruction){0x31, 5, Core6502::AND, Core6502::CPU::indirectYAddr};

    // OR Instructions
    instructions[0x09] = (Core6502::Instruction){0x09, 2, Core6502::ORA, Core6502::CPU::immediate};
    instructions[0x05] = (Core6502::Instruction){0x05, 3, Core6502::ORA, Core6502::CPU::zeroPageAddr};
    instructions[0x15] = (Core6502::Instruction){0x15, 4, Core6502::ORA, Core6502::CPU::zeroPageXAddr};
    instructions[0x0D] = (Core6502::Instruction){0x0D, 4, Core6502::ORA, Core6502::CPU::absoluteAddr};
    instructions[0x1D] = (Core6502::Instruction){0x1D, 4, Core6502::ORA, Core6502::CPU::absoluteXAddr};
    instructions[0x19] = (Core6502::Instruction){0x19, 4, Core6502::ORA, Core6502::CPU::absoluteYAddr};
    instructions[0x01] = (Core6502::Instruction){0x01, 6, Core6502::ORA, Core6502::CPU::indirectXAddr};
    instructions[0x11] = (Core6502::Instruction){0x11, 5, Core6502::ORA, Core6502::CPU::indirectYAddr};

    // EOR Instructions
    instructions[0x49] = (Core6502::Instruction){0x49, 2, Core6502::EOR, Core6502::CPU::immediate};
    instructions[0x45] = (Core6502::Instruction){0x45, 3, Core6502::EOR, Core6502::CPU::zeroPageAddr};
    instructions[0x55] = (Core6502::Instruction){0x55, 4, Core6502::EOR, Core6502::CPU::zeroPageXAddr};
    instructions[0x4D] = (Core6502::Instruction){0x4D, 4, Core6502::EOR, Core6502::CPU::absoluteAddr};
    instructions[0x5D] = (Core6502::Instruction){0x5D, 4, Core6502::EOR, Core6502::CPU::absoluteXAddr};
    instructions[0x59] = (Core6502::Instruction){0x59, 4, Core6502::EOR, Core6502::CPU::absoluteYAddr};
    instructions[0x41] = (Core6502::Instruction){0x41, 6, Core6502::EOR, Core6502::CPU::indirectXAddr};
    instructions[0x51] = (Core6502::Instruction){0x51, 5, Core6502::EOR, Core6502::CPU::indirectYAddr};

    // BIT Instructions
    instructions[0x24] = (Core6502::Instruction){0x24, 3, Core6502::BIT, Core6502::CPU::zeroPageAddr};
    instructions[0x2C] = (Core6502::Instruction){0x2C, 4, Core6502::BIT, Core6502::CPU::absoluteAddr};

    // INC Instructions
    instructions[0xE6] = (Core6502::Instruction){0xE6, 5, Core6502::INC, Core6502::CPU::zeroPageAddr};
    instructions[0xF6] = (Core6502::Instruction){0xF6, 6, Core6502::INC, Core6502::CPU::zeroPageXAddr};
    instructions[0xEE] = (Core6502::Instruction){0xEE, 6, Core6502::INC, Core6502::CPU::absoluteAddr};
    instructions[0xFE] = (Core6502::Instruction){0xFE, 7, Core6502::INC, Core6502::CPU::absoluteXAddr};

    // INX Instructions
    instructions[0xE8] = (Core6502::Instruction){0xE8, 2, Core6502::INX};

    // INY Instructions
    instructions[0xC8] = (Core6502::Instruction){0xC8, 2, Core6502::INY};

    // DEC Instructions
    instructions[0xC6] = (Core6502::Instruction){0xC6, 5, Core6502::DEC, Core6502::CPU::zeroPageAddr};
    instructions[0xD6] = (Core6502::Instruction){0xD6, 6, Core6502::DEC, Core6502::CPU::zeroPageXAddr};
    instructions[0xCE] = (Core6502::Instruction){0xCE, 6, Core6502::DEC, Core6502::CPU::absoluteAddr};
    instructions[0xDE] = (Core6502::Instruction){0xDE, 7, Core6502::DEC, Core6502::CPU::absoluteXAddr};

    // DEX Instructions
    instructions[0xCA] = (Core6502::Instruction){0xCA, 2, Core6502::DEX};
    
    // DEY Instructions
    instructions[0x88] = (Core6502::Instruction){0x88, 2, Core6502::DEY};

    // Transfer Instructions
    instructions[0xAA] = (Core6502::Instruction){0xAA, 2, Core6502::TAX};
    instructions[0xA8] = (Core6502::Instruction){0xA8, 2, Core6502::TAY};
    instructions[0x8A] = (Core6502::Instruction){0x8A, 2, Core6502::TXA};
    instructions[0x98] = (Core6502::Instruction){0x98, 2, Core6502::TYA};

    // JMP Instructions
    instructions[0x4C] = (Core6502::Instruction){0x4C, 3, Core6502::JMP, Core6502::CPU::absoluteAddr};
    instructions[0x6C] = (Core6502::Instruction){0x6C, 5, Core6502::JMP, Core6502::CPU::indirectAddr}; 
    
    // Branch Instructions
    instructions[0x90] = (Core6502::Instruction){0x90, 2, Core6502::BCC, Core6502::CPU::relativeAddr};
    instructions[0xB0] = (Core6502::Instruction){0xB0, 2, Core6502::BCS, Core6502::CPU::relativeAddr};
    instructions[0xF0] = (Core6502::Instruction){0xF0, 2, Core6502::BEQ, Core6502::CPU::relativeAddr};
    instructions[0x30] = (Core6502::Instruction){0x30, 2, Core6502::BMI, Core6502::CPU::relativeAddr};
    instructions[0xD0] = (Core6502::Instruction){0xD0, 2, Core6502::BNE, Core6502::CPU::relativeAddr};
    instructions[0x10] = (Core6502::Instruction){0x10, 2, Core6502::BPL, Core6502::CPU::relativeAddr};
    instructions[0x50] = (Core6502::Instruction){0x50, 2, Core6502::BVC, Core6502::CPU::relativeAddr};
    instructions[0x70] = (Core6502::Instruction){0x70, 2, Core6502::BVS, Core6502::CPU::relativeAddr};

    // Status Flag Instructions
    instructions[0x18] = (Core6502::Instruction){0x18, 2, Core6502::CLC};
    instructions[0xD8] = (Core6502::Instruction){0xD8, 2, Core6502::CLD};
    instructions[0x58] = (Core6502::Instruction){0x58, 2, Core6502::CLI};
    instructions[0xB8] = (Core6502::Instruction){0xB8, 2, Core6502::CLV};
    instructions[0x38] = (Core6502::Instruction){0x38, 2, Core6502::SEC};
    instructions[0xF8] = (Core6502::Instruction){0xF8, 2, Core6502::SED};
    instructions[0x78] = (Core6502::Instruction){0x78, 2, Core6502::SEI};

}