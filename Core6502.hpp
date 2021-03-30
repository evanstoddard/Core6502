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
struct Core6502 {
    
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
        uint8_t CF:1;
        uint8_t ZF:1;
        uint8_t ID:1;
        uint8_t DM:1;
        uint8_t BR:1;
        uint8_t OF:1;
        uint8_t NF:1;
    } status;
    
}

#endif /* Core6502_hpp */
