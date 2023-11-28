#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

    printf("%d\n", CURRENT_STATE.PC);
    int pc = mem_read_32(CURRENT_STATE.PC); //smth about 32-bit alignment
    int op = pc >> 26;
    printf("The Opcode is: %0x\n", op);

    if (op == 0) { //R-TYPE instructions
        int function = pc << 26;
        int rs = (pc >> 21) & 0x1F;
        int rt = (pc >> 16) & 0x1F;
        int rd = (pc >> 11) & 0x1F;
        int sa = (pc >> 6) & 0x1F;

        if (function == 0x20) { //ADD
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x21) { //ADDU
            unsigned int temp = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.REGS[rd] = temp;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x24) { //AND
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x9) { //JALR
            NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
        }
        else if (function = 0x8) { //JR
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
        }
        else if (function == 0x10) { //MFHI
            NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x12) { //MFLO
            NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x18) { //MULT
            long mult = CURRENT_STATE.REGS[rs] * CURRENT_STATE.REGS[rt];
            NEXT_STATE.LO = mult;
            NEXT_STATE.HI = mult >> 32;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x19) { //MULTU

        }
    }

    else { //NOT R-TYPE instructions 
        int rs = (pc >> 21) & 0x1F;
        int rt = (pc >> 16) & 0x1F;
        unsigned short imm = pc & 0xFFFF;

        if (op == 0x8) { //ADDI
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imm;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0x9) { //ADDIU
            unsigned int temp = CURRENT_STATE.REGS[rs] + imm;
            NEXT_STATE.REGS[rt] = temp;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0xC) { //ANDI
            NEXT_STATE.REGS[rt] = 0 | (imm & CURRENT_STATE.REGS[rs]);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0x4) { //BEQ
            if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target; 
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x1 & rt == 0x1) { //BGEZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x1 & rt == 0x11) { //BGEZAL
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;

            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x7 & rt == 0) { //BGTZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0 & CURRENT_STATE.REGS[rs] != 0) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 & rt == 0) { //BLEZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1 | CURRENT_STATE.REGS[rs] == 0) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 & rt == 0) { //BLTZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 & rt == 0) { //BLTZAL
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;

            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x5) { //BNE
            if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
                short target = (short)imm;
                target = target << 2;
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
            }
        }
        else if (op == 023) { //LW
            int vAddr = CURRENT_STATE.REGS[rs] + imm;
            CURRENT_STATE.REGS[rt] = mem_read_32(vAddr);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else { //JUMPS
            unsigned int target = CURRENT_STATE.PC & 0x3FFFFFF; //mask of 26 1's

            if (op == 0x2) { //J
                NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | target << 2;
            }
            else if (op == 0x3) { //JAL
                NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;

                NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | target << 2;
            }
        }
    }
}

/* questions
    does T+1 in link instructions matter?
    how to check for MFHI and MFLO in t-1 and t-2/what does that mean exactly
    do we only modify NEXT_STATE values?
    what exactly does 0 || GPR mean?
    what does No overflow exception occurs under any circumstances mean?
    
*/