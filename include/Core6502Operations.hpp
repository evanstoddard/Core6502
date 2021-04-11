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
        bool protectedInstruction;
        uint8_t opcode;
        uint8_t cycles;
        void (*instructionFunction)(Core6502::CPU&, struct Instruction&);
    };

    // LDA Instructions
    void LDA_Immediate(Core6502::CPU&, struct Instruction&);
    void LDA_Zero_Page(Core6502::CPU&, struct Instruction&);
    void LDA_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void LDA_Absolute(Core6502::CPU&, struct Instruction&);
    void LDA_Absolute_X(Core6502::CPU&, struct Instruction&);
    void LDA_Absolute_Y(Core6502::CPU&, struct Instruction&);
    void LDA_Indirect_X(Core6502::CPU&, struct Instruction&);
    void LDA_Indirect_Y(Core6502::CPU&, struct Instruction&);

    // LDX Instructions
    void LDX_Immediate(Core6502::CPU&, struct Instruction&);
    void LDX_Zero_Page(Core6502::CPU&, struct Instruction&);
    void LDX_Zero_Page_Y(Core6502::CPU&, struct Instruction&);
    void LDX_Absolute(Core6502::CPU&, struct Instruction&);
    void LDX_Absolute_Y(Core6502::CPU&, struct Instruction&);

    // LDY Instructions
    void LDY_Immediate(Core6502::CPU&, struct Instruction&);
    void LDY_Zero_Page(Core6502::CPU&, struct Instruction&);
    void LDY_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void LDY_Absolute(Core6502::CPU&, struct Instruction&);
    void LDY_Absolute_X(Core6502::CPU&, struct Instruction&);

    // STA Instructions
    void STA_Zero_Page(Core6502::CPU&, struct Instruction&);
    void STA_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void STA_Absolute(Core6502::CPU&, struct Instruction&);
    void STA_Absolute_X(Core6502::CPU&, struct Instruction&);
    void STA_Absolute_Y(Core6502::CPU&, struct Instruction&);
    void STA_Indirect_X(Core6502::CPU&, struct Instruction&);
    void STA_Indirect_Y(Core6502::CPU&, struct Instruction&);
    
    // STX Instructions
    void STX_Zero_Page(Core6502::CPU&, struct Instruction&);
    void STX_Zero_Page_Y(Core6502::CPU&, struct Instruction&);
    void STX_Absolute(Core6502::CPU&, struct Instruction&);

    // STY Instructions
    void STY_Zero_Page(Core6502::CPU&, struct Instruction&);
    void STY_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void STY_Absolute(Core6502::CPU&, struct Instruction&);

    // AND Instructions
    void AND_Immediate(Core6502::CPU&, struct Instruction&);
    void AND_Zero_Page(Core6502::CPU&, struct Instruction&);
    void AND_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void AND_Absolute(Core6502::CPU&, struct Instruction&);
    void AND_Absolute_X(Core6502::CPU&, struct Instruction&);
    void AND_Absolute_Y(Core6502::CPU&, struct Instruction&);
    void AND_Indirect_X(Core6502::CPU&, struct Instruction&);
    void AND_Indirect_Y(Core6502::CPU&, struct Instruction&);

     // ORA Instructions
    void ORA_Immediate(Core6502::CPU&, struct Instruction&);
    void ORA_Zero_Page(Core6502::CPU&, struct Instruction&);
    void ORA_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void ORA_Absolute(Core6502::CPU&, struct Instruction&);
    void ORA_Absolute_X(Core6502::CPU&, struct Instruction&);
    void ORA_Absolute_Y(Core6502::CPU&, struct Instruction&);
    void ORA_Indirect_X(Core6502::CPU&, struct Instruction&);
    void ORA_Indirect_Y(Core6502::CPU&, struct Instruction&);

    // EOR Instructions
    void EOR_Immediate(Core6502::CPU&, struct Instruction&);
    void EOR_Zero_Page(Core6502::CPU&, struct Instruction&);
    void EOR_Zero_Page_X(Core6502::CPU&, struct Instruction&);
    void EOR_Absolute(Core6502::CPU&, struct Instruction&);
    void EOR_Absolute_X(Core6502::CPU&, struct Instruction&);
    void EOR_Absolute_Y(Core6502::CPU&, struct Instruction&);
    void EOR_Indirect_X(Core6502::CPU&, struct Instruction&);
    void EOR_Indirect_Y(Core6502::CPU&, struct Instruction&);

    // BIT Instructions
    void BIT_Zero_Page(Core6502::CPU&, struct Instruction&);
    void BIT_Absolute(Core6502::CPU&, struct Instruction&);

    // Transfer Instructions
    void TAX(Core6502::CPU&, struct Instruction&);
    void TAY(Core6502::CPU&, struct Instruction&);
    void TXA(Core6502::CPU&, struct Instruction&);
    void TYA(Core6502::CPU&, struct Instruction&);

    // Status Flag Instructions
    void CLC(Core6502::CPU&, struct Instruction&);
    void CLD(Core6502::CPU&, struct Instruction&);
    void CLI(Core6502::CPU&, struct Instruction&);
    void CLV(Core6502::CPU&, struct Instruction&);
    void SEC(Core6502::CPU&, struct Instruction&);
    void SED(Core6502::CPU&, struct Instruction&);
    void SEI(Core6502::CPU&, struct Instruction&);

}

#endif