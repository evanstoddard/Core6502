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
    

}

#endif