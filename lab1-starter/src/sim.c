#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

    printf("%d\n", CURRENT_STATE.PC);
    uint32_t pc = mem_read_32(CURRENT_STATE.PC); //smth about 32-bit alignment
    uint32_t op = pc >> 26;
    printf("%0x\n", op);

    if (op == 0) {
        //R-TYPE instructions
    }
    else { //NOT R-TYPE instructions 
        int rs = (pc >> 21) & 0x1F;
        int rt = (pc >> 16) & 0x1F;
        uint16_t imm = pc & 0xFFFF;

        if (op == 0x8) { //ADDI
            NEXT_STATE.REGS[rt] = NEXT_STATE.REGS[rt] + imm;
            NEXT_STATE.PC = NEXT_STATE.PC + 4;
        }
        else if (op == 0x9) { //ADDIU
            NEXT_STATE.REGS[rt] = NEXT_STATE.REGS[rt] + imm;
            NEXT_STATE.PC = NEXT_STATE.PC + 4;
        }
    }
}

/* questions

Do we need to handle overflow exceptions in any of the ADD functions? What about signs? NO, typecast
What exactly does task 1.1 mean? Just write your own test
Do we have to check if the program is trying to change register zero? 
What does the 32-bit alginment thing mean? 

*/

