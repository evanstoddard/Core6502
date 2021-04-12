//
//  Core6502Operations.cpp
//  Core6502Operations
//
//  Created by Evan Stoddard on 4/1/21.
//
#include "Core6502.hpp"
#include "Core6502Operations.hpp"
#include <iomanip>
#include <iostream>

// LDA Operations
void Core6502::LDA_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value and store into accumulator
    cpu.registers.A = cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // Load value at index into accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::LDA_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Get Zero Page X address
    uint8_t addr =  cpu.zeroPageXAddr();

    // Load value at addr into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();
    
    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr = cpu.absoluteXAddr();

    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr = cpu.absoluteYAddr();

    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::LDA_Indirect_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Get indirect X address;
    uint16_t addr = cpu.indirectXAddr();

    // Load value from effective address into accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Indirect_Y(Core6502::CPU& cpu, struct Instruction&) {

    // Get Indirect Y address
    uint16_t addr = cpu.indirectYAddr();

    // Load value at effective address into accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// LDX Operations
void Core6502::LDX_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value and store into X
    cpu.registers.X = cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::LDX_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();;

    // Load value at index into X
    // Can directly index memory with fetched addr
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);
}
void Core6502::LDX_Zero_Page_Y(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of Y register
    uint8_t addr =  cpu.zeroPageYAddr();

    // Load value at addr into X
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::LDX_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();
    
    // Load value at address into X
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::LDX_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr = cpu.absoluteYAddr();

    // Load value at address into X
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);
}

// LDY Operations
void Core6502::LDY_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value and store into Y
    cpu.registers.Y = cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::LDY_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // Load value at index into Y
    // Can directly index memory with fetched addr
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);
}
void Core6502::LDY_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr =  cpu.zeroPageXAddr();

    // Load value at addr into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::LDY_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();
    
    // Load value at address into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::LDY_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from X register
    uint16_t addr = cpu.absoluteXAddr();
    // Load value at address into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);
}

// STA Operations
void Core6502::STA_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // Store Accumulator to index
    cpu.mem[addr] = cpu.registers.A;
    
    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::STA_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr = cpu.zeroPageXAddr();

    // Load value from Accumulator into RAM
    cpu.mem[addr] = cpu.registers.A;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}
void Core6502::STA_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();
    
    // Load value from Accumulator into RAM
    cpu.mem[addr] = cpu.registers.A;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}
void Core6502::STA_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = cpu.absoluteXAddr();

    // Load value from Accumulator into RAM
    cpu.mem[addr] = cpu.registers.A;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}
void Core6502::STA_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr = cpu.absoluteYAddr();

    // Load value from Accumulator into RAM
    cpu.mem[addr] = cpu.registers.A;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);
}
void Core6502::STA_Indirect_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch offset and add value in register X
    uint16_t addr = cpu.indirectXAddr();

    // Load value from Accumulator into RAM
    cpu.mem[addr] = cpu.registers.A;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}
void Core6502::STA_Indirect_Y(Core6502::CPU& cpu, struct Instruction&) {

    // Fetch 16-bit address from zero page memory
    uint16_t addr = cpu.indirectYAddr();

    // Load value from Accumulator into RAM
    cpu.mem[addr] = cpu.registers.A;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}

// STX Operations
void Core6502::STX_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // Write X register to RAM
    cpu.mem[addr] = cpu.registers.X;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);
}
void Core6502::STX_Zero_Page_Y(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of Y register
    uint8_t addr = cpu.zeroPageYAddr();

    // Write X register to RAM
    cpu.mem[addr] = cpu.registers.X;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}
void Core6502::STX_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();
    
    // Write X register to RAM
    cpu.mem[addr] = cpu.registers.X;

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr]& 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.mem[addr] == 0);

}

// STY Operations
void Core6502::STY_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // Load value at index into Y
    // Can directly index memory with fetched addr
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);
}
void Core6502::STY_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr = cpu.zeroPageXAddr();

    // Load value at addr into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::STY_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();
    
    // Load value at address into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}

// Transfer Instructions
void Core6502::TAX(Core6502::CPU& cpu, struct Instruction& op) {

    // Transfer Accumulator to X
    cpu.registers.X = cpu.registers.A;

    // Set Zero & Negative Flags
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::TAY(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Transfer Accumulator to Y
    cpu.registers.Y = cpu.registers.A;

    // Set Zero & Negative Flags
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::TXA(Core6502::CPU& cpu, struct Instruction& op) {
   
    // Transfer X to Accumulator
    cpu.registers.A = cpu.registers.X;

    // Set Zero & Negative Flags
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::TYA(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Transfer X to Accumulator
    cpu.registers.A = cpu.registers.Y;

    // Set Zero & Negative Flags
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// AND Operations
void Core6502::AND_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value AND with Accumulator
    cpu.registers.A &= cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::AND_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // And value with accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::AND_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr = cpu.zeroPageXAddr();

    // AND value with Accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::AND_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();

    // AND value with Accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::AND_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr = cpu.absoluteXAddr();
    
    // AND value with Accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::AND_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr = cpu.absoluteYAddr();

    // AND value with Accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::AND_Indirect_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch offset and add value in register X
    uint16_t addr = cpu.indirectXAddr();

    // AND value with Accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::AND_Indirect_Y(Core6502::CPU& cpu, struct Instruction&) {

    // Fetch 16-bit address from zero page memory
    uint16_t addr = cpu.indirectYAddr();

    // AND value with Accumulator
    cpu.registers.A &= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// OR Operations
void Core6502::ORA_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value OR with Accumulator
    cpu.registers.A |= cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::ORA_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();;

    // OR value with accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::ORA_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr = cpu.zeroPageXAddr();

    // OR value with Accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::ORA_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();

    // OR value with Accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::ORA_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr = cpu.absoluteXAddr();

    // OR value with Accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::ORA_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr = cpu.absoluteYAddr();

    // OR value with Accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::ORA_Indirect_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch offset and add value in register X
    uint16_t addr =  cpu.indirectXAddr();

    // OR value with Accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::ORA_Indirect_Y(Core6502::CPU& cpu, struct Instruction&) {

    // Fetch 16-bit address from zero page memory
    uint16_t addr = cpu.indirectYAddr();

    // OR value with Accumulator
    cpu.registers.A |= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// INC Operations
void Core6502::INC_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {

    // Get address
    uint8_t addr = cpu.zeroPageAddr();

    // Increment value at address
    cpu.mem[addr]++;

    // Set flags
    cpu.status.ZeroFlag = (cpu.mem[addr] == 0);
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);

}
void Core6502::INC_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Get address
    uint8_t addr = cpu.zeroPageXAddr();

    // Increment value at address
    cpu.mem[addr]++;

    // Set flags
    cpu.status.ZeroFlag = (cpu.mem[addr] == 0);
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);

}
void Core6502::INC_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Get address
    uint16_t addr = cpu.absoluteAddr();

    // Increment value at address
    cpu.mem[addr] = cpu.mem[addr] + 1;

    // Set flags
    cpu.status.ZeroFlag = (cpu.mem[addr] == 0);
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);

}
void Core6502::INC_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Get address
    uint16_t addr = cpu.absoluteXAddr();

    // Increment value at address
    cpu.mem[addr] = cpu.mem[addr] + 1;

    // Set flags
    cpu.status.ZeroFlag = (cpu.mem[addr] == 0);
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);

}

// EOR Operations
void Core6502::EOR_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value EOR with Accumulator
    cpu.registers.A ^= cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::EOR_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // EOR value with accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::EOR_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr = cpu.zeroPageXAddr();

    // EOR value with Accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::EOR_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr  = cpu.absoluteAddr();
    
    // EOR value with Accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::EOR_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = cpu.absoluteXAddr();

    // EOR value with Accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::EOR_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr  = cpu.absoluteYAddr();

    // EOR value with Accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::EOR_Indirect_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch offset and add value in register X
    uint16_t addr = cpu.indirectXAddr();

    // EOR value with Accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::EOR_Indirect_Y(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address from zero page memory
    uint16_t addr = cpu.indirectYAddr();

    // EOR value with Accumulator
    cpu.registers.A ^= cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// BIT Operations
void Core6502::BIT_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.zeroPageAddr();

    // And value with Accumulator
    uint8_t val = cpu.registers.A & cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.OverflowFlag = (bool)(cpu.mem[addr] & 0b01000000);
    cpu.status.ZeroFlag     = (bool)(val == 0);
}
void Core6502::BIT_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr = cpu.absoluteAddr();

    // AND value with Accumulator
    uint8_t val = cpu.registers.A & cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.OverflowFlag = (bool)(cpu.mem[addr] & 0b01000000);
    cpu.status.ZeroFlag     = (bool)(val == 0);

}

// Status Flag Instructions
void Core6502::CLC(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Carry flag
    cpu.status.CarryFlag = 0;
}
void Core6502::CLD(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Decimal flag
    cpu.status.DecimalMode = 0;
}
void Core6502::CLI(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Interrupt Disable flag
    cpu.status.InterruptDisable = 0;
}
void Core6502::CLV(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Overflow flag
    cpu.status.OverflowFlag = 0;
}
void Core6502::SEC(Core6502::CPU& cpu, struct Instruction& op) {
    // Set Carry flag
    cpu.status.CarryFlag = 1;
}
void Core6502::SED(Core6502::CPU& cpu, struct Instruction& op) {
    // Set Decimal flag
    cpu.status.DecimalMode = 1;
}
void Core6502::SEI(Core6502::CPU& cpu, struct Instruction& op) {
    // Set Interrupt Disable flag
    cpu.status.InterruptDisable = 1;
}