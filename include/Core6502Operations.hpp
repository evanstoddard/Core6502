//
//  Core6502Operations.hpp
//  Core6502Operations
//
//  Created by Evan Stoddard on 4/1/21.
//
#ifndef Core6502Operations_hpp
#define Core6502Operations_hpp

#include <stdint.h>
#include "Core6502.hpp"

namespace Core6502 {
    
    class CPU;

    // Operation struct
    struct Instruction {
        uint8_t opCode;
        uint8_t cycles;
        void (*instructionFunction)(Core6502::CPU&, Core6502::Instruction&);
        uint16_t (*addressFunction)(Core6502::CPU&);
    };

    // Load Register Instructions
    void LDA(Core6502::CPU&, Core6502::Instruction&);
    void LDX(Core6502::CPU&, Core6502::Instruction&);
    void LDY(Core6502::CPU&, Core6502::Instruction&);

    // Store Register Instructions
    void STA(Core6502::CPU&, Core6502::Instruction&);
    void STX(Core6502::CPU&, Core6502::Instruction&);
    void STY(Core6502::CPU&, Core6502::Instruction&);

    // Logic Instructions
    void AND(Core6502::CPU&, Core6502::Instruction&);
    void ORA(Core6502::CPU&, Core6502::Instruction&);
    void EOR(Core6502::CPU&, Core6502::Instruction&);
    void BIT(Core6502::CPU&, Core6502::Instruction&);

    // Increment Instructions
    void INC(Core6502::CPU&, Core6502::Instruction&);
    void INX(Core6502::CPU&, Core6502::Instruction&);
    void INY(Core6502::CPU&, Core6502::Instruction&);
    
    // Decrement Instructions
    void DEC(Core6502::CPU&, Core6502::Instruction&);
    void DEX(Core6502::CPU&, Core6502::Instruction&);
    void DEY(Core6502::CPU&, Core6502::Instruction&);
    
    // Transfer Instructions
    void TAX(Core6502::CPU&, Core6502::Instruction&);
    void TAY(Core6502::CPU&, Core6502::Instruction&);
    void TXA(Core6502::CPU&, Core6502::Instruction&);
    void TYA(Core6502::CPU&, Core6502::Instruction&);

    // JMP Instructions
    void JMP(Core6502::CPU&, Core6502::Instruction&);
   
    // Branch Instructions
    void BCC(Core6502::CPU&, Core6502::Instruction&);
    void BCS(Core6502::CPU&, Core6502::Instruction&);
    void BEQ(Core6502::CPU&, Core6502::Instruction&);
    void BMI(Core6502::CPU&, Core6502::Instruction&);
    void BNE(Core6502::CPU&, Core6502::Instruction&);
    void BPL(Core6502::CPU&, Core6502::Instruction&);
    void BVC(Core6502::CPU&, Core6502::Instruction&);
    void BVS(Core6502::CPU&, Core6502::Instruction&);

    // Status Flag Instructions
    void CLC(Core6502::CPU&, Core6502::Instruction&);
    void CLD(Core6502::CPU&, Core6502::Instruction&);
    void CLI(Core6502::CPU&, Core6502::Instruction&);
    void CLV(Core6502::CPU&, Core6502::Instruction&);
    void SEC(Core6502::CPU&, Core6502::Instruction&);
    void SED(Core6502::CPU&, Core6502::Instruction&);
    void SEI(Core6502::CPU&, Core6502::Instruction&);

}

#endif