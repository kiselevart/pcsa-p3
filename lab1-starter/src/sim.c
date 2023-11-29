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
        else if (function == 0x1A) { //DIV
            if (CURRENT_STATE.REGS[rt] != 0) {
                NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt];
                NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt];
            } 
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function = 0x1B) { //DIVU
            if (CURRENT_STATE.REGS[rt] != 0) {
                unsigned int dividend = CURRENT_STATE.REGS[rs];
                unsigned int divisor = CURRENT_STATE.REGS[rt];
                NEXT_STATE.LO = dividend / divisor;
                NEXT_STATE.HI = dividend % divisor;
            }
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
        else if (function = 0x13) { //MTHI
            NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function = 0x13) { //MTLO
            NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x18) { //MULT
            long mult = CURRENT_STATE.REGS[rs] * CURRENT_STATE.REGS[rt];
            NEXT_STATE.LO = mult;
            NEXT_STATE.HI = mult >> 32;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x19) { //MULTU
            unsigned int a = CURRENT_STATE.REGS[rs];
            unsigned int b = CURRENT_STATE.REGS[rt];
            long mult = a * b;
            NEXT_STATE.LO = mult;
            NEXT_STATE.HI = mult >> 32;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x27) { //NOR
            NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);   
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x25) { //OR
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];   
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x0) { //SLL 
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x4) { //SLLV
            int shift = CURRENT_STATE.REGS[rs] & 0x1F; //five bit mask
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shift;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x2A) { //SLT
            if (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.REGS[rd] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rd] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x2B) { //SLTU
            if ((unsigned)CURRENT_STATE.REGS[rs] < (unsigned)CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.REGS[rd] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rd] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x3) {
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x7) { //SRAV
            int shift = CURRENT_STATE.REGS[rs] & 0x1F; //five bit mask
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shift;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x2) { //SRL
            NEXT_STATE.REGS[rd] = (unsigned)CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x6) { //SRLV
            int shift = CURRENT_STATE.REGS[rs] & 0x1F; //five bit mask
            NEXT_STATE.REGS[rd] = (unsigned)CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x22) { //SUB
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x23) { //SUBU
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0xC) { //SYSCALL
            if (CURRENT_STATE.REGS[2] == 0x0A) {
                RUN_BIT = FALSE;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == 0x26) { //XOR
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
    }

    else { //NOT R-TYPE instructions 
        //decode current instruction
        int rs = (pc >> 21) & 0x1F;
        int rt = (pc >> 16) & 0x1F;
        unsigned short imm = pc & 0xFFFF;

        //used in branch instructions
        short target = (short)imm; 
        target = target << 2;

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
                NEXT_STATE.PC = CURRENT_STATE.PC + target; 
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x1 & rt == 0x1) { //BGEZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0) {
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
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x7 & rt == 0) { //BGTZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0 & CURRENT_STATE.REGS[rs] != 0) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 & rt == 0) { //BLEZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1 | CURRENT_STATE.REGS[rs] == 0) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 & rt == 0) { //BLTZ
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1) {
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
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x5) { //BNE
            if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
            }
        }
        else if (op == 0x20) { //LB

        }
        else if (op == 0x24) { //LBU

        }
        else if (op == 0x21) { //LH

        }
        else if (op == 0x25) { //LHU
        
        }
        else if (op == 0xF) { //LUI
            NEXT_STATE.REGS[rt] == imm << 16;
        }
        else if (op == 0x23) { //LW
            //NOT SURE ABOUT THIS ONE
            int vAddr = CURRENT_STATE.REGS[rs] + imm;
            NEXT_STATE.REGS[rt] = mem_read_32(vAddr);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0x13) { //ORI
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | imm;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0x28) { //SB

        }
        else if (op == 0x29) { //SH
        
        }
        else if (op == 0xA) { //SLTI
            if (CURRENT_STATE.REGS[rs] < (short)imm) {
                NEXT_STATE.REGS[rt] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rt] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0xB) { //SLTIU
            if ((unsigned)CURRENT_STATE.REGS[rs] < (short)imm) {
                NEXT_STATE.REGS[rt] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rt] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0x2B) { //SW
            unsigned int vAddr = CURRENT_STATE.REGS[rs] + imm;
            mem_write_32(vAddr, CURRENT_STATE.REGS[rt]);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == 0xE) { //XOR
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ imm; 
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

*/