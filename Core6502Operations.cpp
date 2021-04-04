//
//  Core6502Operations.cpp
//  Core6502Operations
//
//  Created by Evan Stoddard on 4/1/21.
//
#include "Core6502.hpp"
#include "Core6502Operations.hpp"

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
    uint8_t addr = cpu.fetchByte();

    // Load value at index into accumulator
    // Can directly index memory with fetched addr
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
}
void Core6502::LDA_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr =  cpu.fetchByte();
            addr += cpu.registers.X;

    // Load value at addr into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
    
    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.X;

    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

}
void Core6502::LDA_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.Y;

    // Load value at address into Accumulator
    cpu.registers.A = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);
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
    cpu.status.NegativeFlag = (bool)(cpu.registers.A & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.A == 0);

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
    uint8_t addr = cpu.fetchByte();

    // Load value at index into X
    // Can directly index memory with fetched addr
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);
}
void Core6502::LDX_Zero_Page_Y(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of Y register
    uint8_t addr =  cpu.fetchByte();
            addr += cpu.registers.Y;

    // Load value at addr into X
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::LDX_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
    
    // Load value at address into X
    cpu.registers.X = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.X & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.X == 0);

}
void Core6502::LDX_Absolute_Y(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from Y register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.Y;

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
    uint8_t addr = cpu.fetchByte();

    // Load value at index into Y
    // Can directly index memory with fetched addr
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);
}
void Core6502::LDY_Zero_Page_X(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch Offset and add value of X register
    uint8_t addr =  cpu.fetchByte();
            addr += cpu.registers.X;

    // Load value at addr into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::LDY_Absolute(Core6502::CPU& cpu, struct Instruction& op) {

    // Fetch 16-bit address
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
    
    // Load value at address into Y
    cpu.registers.Y = cpu.mem[addr];

    // Set Zero & Negative Flags appropriately
    cpu.status.NegativeFlag = (bool)(cpu.registers.Y & 0b10000000);
    cpu.status.ZeroFlag     = (bool)(cpu.registers.Y == 0);

}
void Core6502::LDY_Absolute_X(Core6502::CPU& cpu, struct Instruction& op) {
    // Fetch 16-bit address and add offset from X register
    uint16_t addr  = cpu.fetchByte();
             addr += (cpu.fetchByte() << 8);
             addr += cpu.registers.X;

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