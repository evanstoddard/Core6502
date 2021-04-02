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
    
    // Operation struct
    struct Operation {
        bool protectedOperation;
        uint8_t opcode;
        uint8_t cycles;
        void (*operationFunction)(struct CPU&, struct Operation&);
    };

    // LDA Operations
    void LDA_Immediate(struct CPU&, struct Operation&);
    void LDA_Zero_Page(struct CPU&, struct Operation&);
    void LDA_Zero_Page_X(struct CPU&, struct Operation&);
    void LDA_Absolute(struct CPU&, struct Operation&);
    void LDA_Absolute_X(struct CPU&, struct Operation&);
    void LDA_Absolute_Y(struct CPU&, struct Operation&);
    void LDA_Indirect_X(struct CPU&, struct Operation&);
    void LDA_Indirect_Y(struct CPU&, struct Operation&);

}

#endif