//
//  Core6502Operations.cpp
//  Core6502Operations
//
//  Created by Evan Stoddard on 4/1/21.
//
#include "Core6502.hpp"
#include "Core6502Operations.hpp"

void LDA_Immediate(struct CPU& cpu, struct Operation& op) {

}
Core6502::CPU.instructions[0xA9] = {true, 0xA9, 2, LDA_Immediate};

// void LDA_Zero_Page(struct CPU&, struct Operation&);
// void LDA_Zero_Page_X(struct CPU&, struct Operation&);
// void LDA_Absolute(struct CPU&, struct Operation&);
// void LDA_Absolute_X(struct CPU&, struct Operation&);
// void LDA_Absolute_Y(struct CPU&, struct Operation&);
// void LDA_Indirect_X(struct CPU&, struct Operation&);
// void LDA_Indirect_Y(struct CPU&, struct Operation&);