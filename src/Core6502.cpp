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
    registers.SP    = 0xFF;
    registers.A     = 0x0;
    registers.X     = 0x0;
    registers.Y     = 0x0;

    // Set flags to a default state and disable interrupts
    status.bitfield.BreakCommand = 0;
    status.bitfield.CarryFlag = 0;
    status.bitfield.DecimalMode = 0;
    status.bitfield.InterruptDisable = 1;
    status.bitfield.NegativeFlag = 0;
    status.bitfield.OverflowFlag = 0;
    status.bitfield.UserFlag = 0;
    status.bitfield.ZeroFlag = 1;

    // Set the program counter to address at reset vector
    uint16_t effective_addr  = fetchByte() | (fetchByte() << 8);
    registers.PC = effective_addr;

    // Reset internals
    cyclesRemaining = 0;

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

void Core6502::CPU::clock() {

    // If cycles remaining is zero, fetch opcode and execute
    if (!cyclesRemaining) {
        
        // Set instruction and remaining cycles
        Core6502::Instruction & inst = instructions[fetchByte()];
        cyclesRemaining = inst.cycles - 1;

        // Execute instruction
        inst.instructionFunction(*this, inst);

    } else {

        // Decrement cycles remaining
        cyclesRemaining--;
    }

}

void Core6502::CPU::irq() {

    // Interrupt if enabled
    if (!status.bitfield.InterruptDisable) {
        // Push PC onto stack
        mem[registers.SP] = (uint8_t)(registers.PC >> 8);
        registers.SP--;
        mem[registers.SP] = (uint8_t)(registers.PC & 0xFF);
        registers.SP--;

        // Push cpu status onto stack
        mem[registers.SP] = status.raw;
        registers.SP--;

        // Set PC to IRQ vector
        registers.PC =  mem[0xFFFF] << 8;
        registers.PC |= mem[0xFFFE];

        // Set break status
        status.bitfield.BreakCommand = 0x1;
    }

}

void Core6502::CPU::nmi() {

    // Push PC onto stack
    mem[registers.SP] = (uint8_t)(registers.PC >> 8);
    registers.SP--;
    mem[registers.SP] = (uint8_t)(registers.PC & 0xFF);
    registers.SP--;

    // Push cpu status onto stack
    mem[registers.SP] = status.raw;
    registers.SP--;

    // Set PC to IRQ vector
    registers.PC =  mem[0xFFFB];
    registers.PC |= mem[0xFFFA] << 8;

    // Set break status
    status.bitfield.BreakCommand = 0x1;

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
uint16_t Core6502::CPU::accumlatorAddr(Core6502::CPU &cpu) {
    return cpu.registers.A;
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

    // ROL Instructions
    instructions[0x2A] = (Core6502::Instruction){0x2A, 2, Core6502::ROL, Core6502::CPU::accumlatorAddr};
    instructions[0x26] = (Core6502::Instruction){0x26, 5, Core6502::ROL, Core6502::CPU::zeroPageAddr};
    instructions[0x36] = (Core6502::Instruction){0x36, 6, Core6502::ROL, Core6502::CPU::zeroPageXAddr};
    instructions[0x2E] = (Core6502::Instruction){0x2E, 6, Core6502::ROL, Core6502::CPU::absoluteAddr};
    instructions[0x3E] = (Core6502::Instruction){0x3E, 7, Core6502::ROL, Core6502::CPU::absoluteXAddr};

    // ROR Instructions
    instructions[0x6A] = (Core6502::Instruction){0x6A, 2, Core6502::ROR, Core6502::CPU::accumlatorAddr};
    instructions[0x66] = (Core6502::Instruction){0x66, 5, Core6502::ROR, Core6502::CPU::zeroPageAddr};
    instructions[0x76] = (Core6502::Instruction){0x76, 6, Core6502::ROR, Core6502::CPU::zeroPageXAddr};
    instructions[0x6E] = (Core6502::Instruction){0x6E, 6, Core6502::ROR, Core6502::CPU::absoluteAddr};
    instructions[0x7E] = (Core6502::Instruction){0x7E, 7, Core6502::ROR, Core6502::CPU::absoluteXAddr};

    // ASL Instructions
    instructions[0x0A] = (Core6502::Instruction){0x0A, 2, Core6502::ASL, Core6502::CPU::accumlatorAddr};
    instructions[0x06] = (Core6502::Instruction){0x06, 5, Core6502::ASL, Core6502::CPU::zeroPageAddr};
    instructions[0x16] = (Core6502::Instruction){0x16, 6, Core6502::ASL, Core6502::CPU::zeroPageXAddr};
    instructions[0x0E] = (Core6502::Instruction){0x0E, 6, Core6502::ASL, Core6502::CPU::absoluteAddr};
    instructions[0x1E] = (Core6502::Instruction){0x1E, 7, Core6502::ASL, Core6502::CPU::absoluteXAddr};

    // LSR Instructions
    instructions[0x4A] = (Core6502::Instruction){0x4A, 2, Core6502::LSR, Core6502::CPU::accumlatorAddr};
    instructions[0x46] = (Core6502::Instruction){0x46, 5, Core6502::LSR, Core6502::CPU::zeroPageAddr};
    instructions[0x56] = (Core6502::Instruction){0x56, 6, Core6502::LSR, Core6502::CPU::zeroPageXAddr};
    instructions[0x4E] = (Core6502::Instruction){0x4E, 6, Core6502::LSR, Core6502::CPU::absoluteAddr};
    instructions[0x5E] = (Core6502::Instruction){0x5E, 7, Core6502::LSR, Core6502::CPU::absoluteXAddr};

    // BIT Instructions
    instructions[0x24] = (Core6502::Instruction){0x24, 3, Core6502::BIT, Core6502::CPU::zeroPageAddr};
    instructions[0x2C] = (Core6502::Instruction){0x2C, 4, Core6502::BIT, Core6502::CPU::absoluteAddr};

    // CMP Instructions
    instructions[0xC9] = (Core6502::Instruction){0xC9, 2, Core6502::CMP, Core6502::CPU::immediate};
    instructions[0xC5] = (Core6502::Instruction){0xC5, 3, Core6502::CMP, Core6502::CPU::zeroPageAddr};
    instructions[0xD5] = (Core6502::Instruction){0xD5, 4, Core6502::CMP, Core6502::CPU::zeroPageXAddr};
    instructions[0xCD] = (Core6502::Instruction){0xCD, 4, Core6502::CMP, Core6502::CPU::absoluteAddr};
    instructions[0xDD] = (Core6502::Instruction){0xDD, 4, Core6502::CMP, Core6502::CPU::absoluteXAddr};
    instructions[0xD9] = (Core6502::Instruction){0xD9, 4, Core6502::CMP, Core6502::CPU::absoluteYAddr};
    instructions[0xC1] = (Core6502::Instruction){0xC1, 6, Core6502::CMP, Core6502::CPU::indirectXAddr};
    instructions[0xD1] = (Core6502::Instruction){0xD1, 5, Core6502::CMP, Core6502::CPU::indirectYAddr};

    // CPX Instructions
    instructions[0xE0] = (Core6502::Instruction){0xE0, 2, Core6502::CPX, Core6502::CPU::immediate};
    instructions[0xE4] = (Core6502::Instruction){0xE4, 3, Core6502::CPX, Core6502::CPU::zeroPageAddr};
    instructions[0xEC] = (Core6502::Instruction){0xEC, 4, Core6502::CPX, Core6502::CPU::absoluteAddr};

    // CPY Instructions
    instructions[0xC0] = (Core6502::Instruction){0xC0, 2, Core6502::CPY, Core6502::CPU::immediate};
    instructions[0xC4] = (Core6502::Instruction){0xC4, 3, Core6502::CPY, Core6502::CPU::zeroPageAddr};
    instructions[0xCC] = (Core6502::Instruction){0xCC, 4, Core6502::CPY, Core6502::CPU::absoluteAddr};

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

    // ADC Instructions
    instructions[0x69] = (Core6502::Instruction){0x69, 2, Core6502::ADC, Core6502::CPU::immediate};
    instructions[0x65] = (Core6502::Instruction){0x65, 3, Core6502::ADC, Core6502::CPU::zeroPageAddr};
    instructions[0x75] = (Core6502::Instruction){0x75, 4, Core6502::ADC, Core6502::CPU::zeroPageXAddr};
    instructions[0x6D] = (Core6502::Instruction){0x6D, 4, Core6502::ADC, Core6502::CPU::absoluteAddr};
    instructions[0x7D] = (Core6502::Instruction){0x7D, 4, Core6502::ADC, Core6502::CPU::absoluteXAddr};
    instructions[0x79] = (Core6502::Instruction){0x79, 4, Core6502::ADC, Core6502::CPU::absoluteYAddr};
    instructions[0x61] = (Core6502::Instruction){0x61, 6, Core6502::ADC, Core6502::CPU::indirectXAddr};
    instructions[0x71] = (Core6502::Instruction){0x71, 5, Core6502::ADC, Core6502::CPU::indirectYAddr};

    // SBC Instructions
    instructions[0xE9] = (Core6502::Instruction){0xE9, 2, Core6502::SBC, Core6502::CPU::immediate};
    instructions[0xE5] = (Core6502::Instruction){0xE5, 3, Core6502::SBC, Core6502::CPU::zeroPageAddr};
    instructions[0xF5] = (Core6502::Instruction){0xF5, 4, Core6502::SBC, Core6502::CPU::zeroPageXAddr};
    instructions[0xED] = (Core6502::Instruction){0xED, 4, Core6502::SBC, Core6502::CPU::absoluteAddr};
    instructions[0xFD] = (Core6502::Instruction){0xFD, 4, Core6502::SBC, Core6502::CPU::absoluteXAddr};
    instructions[0xF9] = (Core6502::Instruction){0xF9, 4, Core6502::SBC, Core6502::CPU::absoluteYAddr};
    instructions[0xE1] = (Core6502::Instruction){0xE1, 6, Core6502::SBC, Core6502::CPU::indirectXAddr};
    instructions[0xF1] = (Core6502::Instruction){0xF1, 5, Core6502::SBC, Core6502::CPU::indirectYAddr};

    // Transfer Instructions
    instructions[0xAA] = (Core6502::Instruction){0xAA, 2, Core6502::TAX};
    instructions[0xA8] = (Core6502::Instruction){0xA8, 2, Core6502::TAY};
    instructions[0x8A] = (Core6502::Instruction){0x8A, 2, Core6502::TXA};
    instructions[0x98] = (Core6502::Instruction){0x98, 2, Core6502::TYA};

    // JMP Instructions
    instructions[0x4C] = (Core6502::Instruction){0x4C, 3, Core6502::JMP, Core6502::CPU::absoluteAddr};
    instructions[0x6C] = (Core6502::Instruction){0x6C, 5, Core6502::JMP, Core6502::CPU::indirectAddr}; 
    instructions[0x20] = (Core6502::Instruction){0x20, 6, Core6502::JSR, Core6502::CPU::absoluteAddr};
    instructions[0x60] = (Core6502::Instruction){0x60, 6, Core6502::RTS};

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

    // Stack Instructions
    instructions[0xBA] = (Core6502::Instruction){0xBA, 2, Core6502::TSX};
    instructions[0x9A] = (Core6502::Instruction){0x9A, 2, Core6502::TXS};
    instructions[0x48] = (Core6502::Instruction){0x48, 3, Core6502::PHA};
    instructions[0x08] = (Core6502::Instruction){0x08, 3, Core6502::PHP};
    instructions[0x68] = (Core6502::Instruction){0x68, 4, Core6502::PLA};
    instructions[0x28] = (Core6502::Instruction){0x28, 4, Core6502::PLP};

    // Break/RTI
    instructions[0x00] = (Core6502::Instruction){0x00, 7, Core6502::BRK};
    instructions[0x40] = (Core6502::Instruction){0x40, 6, Core6502::RTI};

    // Misc.
    instructions[0xEA] = (Core6502::Instruction){0xEA, 2, Core6502::NOP};

}