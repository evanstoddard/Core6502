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
#include "Core6502Operations.hpp"

namespace Core6502{

    class CPU {
    
    public:
    CPU();
    CPU(uint8_t * memPtr);

    // Map of operations.  Can be used to overload default operations or add functionality
    // to undocumented operations like the NES Processor.
    std::map<uint8_t, struct Instruction> instructions;

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

    // Methods
    uint8_t fetchByte(); // Fetches current byte and increments PC
    void reset();        // Resets Processor

    volatile uint8_t * mem;

    private:
    void setupInstructionMap();
    
};


}

#endif /* Core6502_hpp */
