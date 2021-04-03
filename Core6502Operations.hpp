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


}

#endif