//
//  Core6502Operations.cpp
//  Core6502Operations
//
//  Created by Evan Stoddard on 4/1/21.
//
#include "Core6502.hpp"
#include "Core6502Operations.hpp"

void Core6502::LDA_Immediate(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Value and store into accumulator
    cpu.registers.A = cpu.fetchByte();

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;

}
void Core6502::LDA_Zero_Page(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch Zero Page address
    uint8_t addr = cpu.fetchByte();

    // Load value at index into accumulator
    // Can directly index memory with fetched addr
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;
}
void Core6502::LDA_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr =  cpu.fetchByte();
            addr += cpu.registers.X;

    // Load value at addr into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;

}
void Core6502::LDA_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
    
    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;

}
void Core6502::LDA_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.X;

    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;

}
void Core6502::LDA_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.Y;

    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;
}
void Core6502::LDA_Indirect_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch offset and add value in register X
    uint8_t zero_addr =  cpu.fetchByte();
            zero_addr += cpu.registers.X;
    
    // Read 16-bit address from zero page address
    uint16_t effective_addr =  cpu.mem[zero_addr];
             effective_addr += (cpu.mem[zero_addr + 1] << 8);

    // Load value from effective address into accumulator
    cpu.registers.A = cpu.mem[effective_addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;

}
void Core6502::LDA_Indirect_Y(Core6502::CPU& cpu, struct Instruction&) {

    // Fetch 16-bit address from zero page memory
    uint8_t offset = cpu.fetchByte();
    uint16_t effective_addr =  cpu.mem[offset];
             effective_addr += (cpu.mem[offset + 1] << 8);

    // Add Y to effecting address
    effective_addr += cpu.registers.Y;

    // Load value at effective address into accumulator
    cpu.registers.A = cpu.mem[effective_addr];

    // Set Zero & Negative Flags appropriately
    if (cpu.registers.A & 0b10000000)   cpu.status.NegativeFlag = 1;
    if (cpu.registers.A == 0)           cpu.status.ZeroFlag = 1;

}