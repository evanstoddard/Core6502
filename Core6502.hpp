//
//  Core6502.hpp
//  Core6502
//
//  Created by Evan Stoddard on 3/30/21.
//

#ifndef Core6502_hpp
#define Core6502_hpp

#include <stdio.h>
#include <stdint.h>
#include <map>

struct Core6502 {
    
    // Operation struct
    struct Operation {
        bool protectedOperation;
        uint8_t opcode;
        uint8_t cycles;
        void (*operationFunction)(Core6502&, Operation&);
    };

    // Map of operations.  Can be used to overload default operations or add functionality
    // to undocumented operations like the NES Processor.
    std::map<uint8_t, struct Operation> operations;

    // Registers
    struct {
        uint16_t PC;
        uint8_t  SP;
        uint8_t  A;
        uint8_t  X;
        uint8_t  Y;
    } registers;
    
    // Processor Status
    struct {
        uint8_t CarryFlag:1;
        uint8_t ZeroFlag:1;
        uint8_t InterruptDisable:1;
        uint8_t DecimalMode:1;
        uint8_t BreakCommand:1;
        uint8_t OverflowFlag:1;
        uint8_t NegativeFlag:1;
        uint8_t UserFlag:1;
    } status;
    
};

#endif /* Core6502_hpp */
