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
    
    // Constructors/Destructors
    public:
        CPU();
        CPU(uint8_t * memPtr);
    // Internals
    public:
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
        union{
            struct {
                uint8_t CarryFlag:1;
                uint8_t ZeroFlag:1;
                uint8_t InterruptDisable:1;
                uint8_t DecimalMode:1;
                uint8_t BreakCommand:1;
                uint8_t OverflowFlag:1;
                uint8_t NegativeFlag:1;
                uint8_t UserFlag:1;
            } bitfield;
            uint8_t raw;
        } status;

        volatile uint8_t * mem;

        uint8_t cyclesRemaining;

    // Fetch Methods
    public:
        uint8_t fetchByte();                            // Fetches current byte and increments PC
        uint8_t fetchFromMemory(Core6502::Instruction& );  // Fetches value from address 

    // Control Methods
    public:
        void clock();               // Clocks processor
        void irq();                 // Interrupts processor if enabled
        void nmi();                 // Performs interrupt regardless of interrupt enabled status
        void reset();               // Resets Processor
    
    // Addressing methods
    public:
        static uint16_t immediate(Core6502::CPU&);
        static uint16_t zeroPageAddr(Core6502::CPU&);
        static uint16_t zeroPageXAddr(Core6502::CPU&);
        static uint16_t zeroPageYAddr(Core6502::CPU&);
        static uint16_t absoluteAddr(Core6502::CPU&);
        static uint16_t absoluteXAddr(Core6502::CPU&);
        static uint16_t absoluteYAddr(Core6502::CPU&);
        static uint16_t indirectXAddr(Core6502::CPU&);
        static uint16_t indirectYAddr(Core6502::CPU&);
        static uint16_t indirectAddr(Core6502::CPU&);
        static uint16_t relativeAddr(Core6502::CPU&);
        static uint16_t accumlatorAddr(Core6502::CPU&);
        
    private:
        void setupInstructionMap();
    };


}

#endif /* Core6502_hpp */
