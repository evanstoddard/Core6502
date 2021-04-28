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


void Core6502::LDA(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value and store into accumulator
    cpu.registers.A = cpu.fetchFromMemory(op);

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// LDX Operations
void Core6502::LDX(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value and store into X
    cpu.registers.X = cpu.fetchFromMemory(op);

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.X == 0);

}

// // LDY Operation
void Core6502::LDY(Core6502::CPU& cpu, struct Instruction& op) {
 
    // Fetch Value and store into Y
    cpu.registers.Y = cpu.fetchFromMemory(op);
 
    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.Y == 0);
 
}

// STA Operation
void Core6502::STA(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint16_t addr = op.addressFunction(cpu);

    // Store Accumulator to index
    cpu.mem[addr] = cpu.registers.A;
    
    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);
}

// STX Operations
void Core6502::STX(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = op.addressFunction(cpu);
 
    // Write X register to RAM
    cpu.mem[addr] = cpu.registers.X;
 
    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.mem[addr] == 0);
}

// STY Operations
void Core6502::STY(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = op.addressFunction(cpu);

    // Load value at index into Y
    // Can directly index memory with fetched addr
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.Y == 0);
}

// Transfer Instructions
void Core6502::TAX(Core6502::CPU& cpu, struct Instruction& op) {

    // Transfer Accumulator to X
    cpu.registers.X = cpu.registers.A;

    // Set Zero & Negative Flags
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::TAY(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Transfer Accumulator to Y
    cpu.registers.Y = cpu.registers.A;

    // Set Zero & Negative Flags
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::TXA(Core6502::CPU& cpu, struct Instruction& op) {
   
    // Transfer X to Accumulator
    cpu.registers.A = cpu.registers.X;

    // Set Zero & Negative Flags
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::TYA(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Transfer X to Accumulator
    cpu.registers.A = cpu.registers.Y;

    // Set Zero & Negative Flags
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// AND Operations
void Core6502::AND(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value AND with Accumulator
    cpu.registers.A &= cpu.fetchFromMemory(op);

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// OR Operations
void Core6502::ORA(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value OR with Accumulator
    cpu.registers.A |= cpu.fetchFromMemory(op);

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// EOR Operations
void Core6502::EOR(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value EOR with Accumulator
    cpu.registers.A ^= cpu.fetchFromMemory(op);

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

// INC Operations
void Core6502::INC(Core6502::CPU& cpu, struct Instruction& op) {

    // Get address
    uint16_t addr = op.addressFunction(cpu);

    // Increment value at address
    cpu.mem[addr]++;

    // Set flags
    cpu.status.bitfield.ZeroFlag = (cpu.mem[addr] == 0);
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);

}

// INX Operation
void Core6502::INX(Core6502::CPU& cpu, struct Instruction& op) {

    // Increment X register
    cpu.registers.X++;

    // Set flags
    cpu.status.bitfield.ZeroFlag = (cpu.registers.X == 0);
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);

}

// INY Operation
void Core6502::INY(Core6502::CPU& cpu, struct Instruction& op) {

    // Increment Y register
    cpu.registers.Y++;

    // Set flags
    cpu.status.bitfield.ZeroFlag = (cpu.registers.Y == 0);
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);

}

// DEC Operations
void Core6502::DEC(Core6502::CPU& cpu, struct Instruction& op) {

    // Get address
    uint16_t addr = op.addressFunction(cpu);

    // Decrement value at address
    cpu.mem[addr]--;

    // Set flags
    cpu.status.bitfield.ZeroFlag = (cpu.mem[addr] == 0);
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);

}
// DEX Operation
void Core6502::DEX(Core6502::CPU& cpu, struct Instruction& op) {

    // Decrement X register
    cpu.registers.X--;

    // Set flags
    cpu.status.bitfield.ZeroFlag = (cpu.registers.X == 0);
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);

}

// DEY Operation
void Core6502::DEY(Core6502::CPU& cpu, struct Instruction& op) {

    // Decrement Y register
    cpu.registers.Y--;

    // Set flags
    cpu.status.bitfield.ZeroFlag = (cpu.registers.Y == 0);
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);

}

// BIT Operations
void Core6502::BIT(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint16_t addr = op.addressFunction(cpu);

    // And value with Accumulator
    uint8_t val = cpu.registers.A & cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.mem[addr] & 0b10000000);
    cpu.status.bitfield.OverflowFlag = (bool)(cpu.mem[addr] & 0b01000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(val == 0);
}


// JMP Operations
void Core6502::JMP(Core6502::CPU& cpu, struct Instruction& op) {

    // Get get absolute address
    uint16_t addr = op.addressFunction(cpu);

    // Set program counter to address
    cpu.registers.PC = addr;

}

 // Branch Instructions
void Core6502::BCC(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.CarryFlag == 0) cpu.registers.PC = addr;
}
void Core6502::BCS(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.CarryFlag) cpu.registers.PC = addr;
}
void Core6502::BEQ(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.ZeroFlag) cpu.registers.PC = addr;
}
void Core6502::BMI(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.NegativeFlag) cpu.registers.PC = addr;
}
void Core6502::BNE(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.ZeroFlag == 0) cpu.registers.PC = addr;
}
void Core6502::BPL(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.NegativeFlag == 0) cpu.registers.PC = addr;
}
void Core6502::BVC(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.OverflowFlag == 0) cpu.registers.PC = addr;
}
void Core6502::BVS(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Branch Address
    uint16_t addr = op.addressFunction(cpu);

    if (cpu.status.bitfield.OverflowFlag) cpu.registers.PC = addr;
}

// Status Flag Instructions
void Core6502::CLC(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Carry flag
    cpu.status.bitfield.CarryFlag = 0;
}
void Core6502::CLD(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Decimal flag
    cpu.status.bitfield.DecimalMode = 0;
}
void Core6502::CLI(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Interrupt Disable flag
    cpu.status.bitfield.InterruptDisable = 0;
}
void Core6502::CLV(Core6502::CPU& cpu, struct Instruction& op) {
    // Clear Overflow flag
    cpu.status.bitfield.OverflowFlag = 0;
}
void Core6502::SEC(Core6502::CPU& cpu, struct Instruction& op) {
    // Set Carry flag
    cpu.status.bitfield.CarryFlag = 1;
}
void Core6502::SED(Core6502::CPU& cpu, struct Instruction& op) {
    // Set Decimal flag
    cpu.status.bitfield.DecimalMode = 1;
}
void Core6502::SEI(Core6502::CPU& cpu, struct Instruction& op) {
    // Set Interrupt Disable flag
    cpu.status.bitfield.InterruptDisable = 1;
}

// Stack Operations
void Core6502::TSX(Core6502::CPU& cpu, struct Instruction& op) {
    // Copy stack pointer value to register X
    uint16_t addr  = cpu.registers.SP;
             addr += (0x01 << 8);
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.X == 0);
}

void Core6502::TXS(Core6502::CPU& cpu, struct Instruction& op) {
    // Copy register x value to stack pointer addr
    uint16_t addr  = cpu.registers.SP;
             addr += (0x01 << 8);
    cpu.mem[addr] = cpu.registers.X;
}

void Core6502::PHA(Core6502::CPU& cpu, struct Instruction& op) {

    // Write accumulator on stack
    uint16_t addr  = cpu.registers.SP;
             addr += (0x01 << 8);
    cpu.mem[addr] = cpu.registers.A;

    // Decrement SP value
    cpu.registers.SP--;

}

void Core6502::PHP(Core6502::CPU& cpu, struct Instruction& op) {

    // Write status on stack
    uint16_t addr  = cpu.registers.SP;
             addr += (0x01 << 8);
    cpu.mem[addr] = cpu.status.raw;

    // Decrement SP value
    cpu.registers.SP--;

}

void Core6502::PLA(Core6502::CPU& cpu, struct Instruction& op) {

    // Increment SP value
    cpu.registers.SP++;

    // Write accumulator on stack
    uint16_t addr  = cpu.registers.SP;
             addr += (0x01 << 8);
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.bitfield.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.bitfield.ZeroFlag     = (bool)(cpu.registers.A == 0);

}

void Core6502::PLP(Core6502::CPU& cpu, struct Instruction& op) {

    // Increment SP value
    cpu.registers.SP++;

    // Write status on stack
    uint16_t addr  = cpu.registers.SP;
             addr += (0x01 << 8);

    cpu.status.raw = cpu.mem[addr];

}


void Core6502::NOP(Core6502::CPU& cpu, struct Instruction& op) {
    // Do nothing...
}