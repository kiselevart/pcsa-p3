#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

//most of the instruction codes
#define ADD 0x20
#define ADDU 0x21
#define AND 0x24
#define DIV 0x1A
#define DIVU 0x1B
#define JALR 0x9
#define JR 0x8
#define MFHI 0x10
#define MFLO 0x12
#define MTHI 0x11
#define MTLO 0x13
#define MULT 0x18
#define MULTU 0x19
#define NOR 0x27
#define OR 0x25
#define SLL 0x0
#define SLLV 0x4
#define SLT 0x2A
#define SLTU 0x2B
#define SRA 0x3
#define SRAV 0x7
#define SRL 0x2
#define SRLV 0x6
#define SUB 0x22
#define SUBU 0x23
#define SYSCALL 0xC
#define XOR 0x26
#define ADDI 0x8
#define ADDIU 0x9
#define ANDI 0xC
#define BEQ 0x4
#define BNE 0x5
#define LB 0x20
#define LBU 0x24
#define LH 0x21
#define LHU 0x25
#define LUI 0xF
#define LW 0x23
#define ORI 0x13
#define SB 0x28
#define SH 0x29
#define SLTI 0xA
#define SLTIU 0xB
#define SW 0x2B
#define XORI 0xE
#define J 0x2
#define JAL 0x3

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

    printf("%d\n", CURRENT_STATE.PC);
    unsigned int pc = mem_read_32(CURRENT_STATE.PC); 
    int op = pc >> 26;
    printf("The Opcode is: %0x\n", op);

    if (op == 0) { //R-TYPE instructions
        int function = pc & 0x3F;
        int rs = (pc >> 21) & 0x1F;
        int rt = (pc >> 16) & 0x1F;
        int rd = (pc >> 11) & 0x1F;
        int sa = (pc >> 6) & 0x1F;
        printf("function is: %0x\n", function);

        if (function == ADD) { 
            printf("ADD\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == ADDU) {
            printf("ADDU\n");
            unsigned int temp = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
            NEXT_STATE.REGS[rd] = temp;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == AND) { 
            printf("AND\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == DIV) {
            printf("DIV\n");
            if (CURRENT_STATE.REGS[rt] != 0) {
                NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt];
                NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt];
            } 
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == DIVU) {
            printf("DIVU\n");
            if (CURRENT_STATE.REGS[rt] != 0) {
                unsigned int dividend = CURRENT_STATE.REGS[rs];
                unsigned int divisor = CURRENT_STATE.REGS[rt];
                NEXT_STATE.LO = dividend / divisor;
                NEXT_STATE.HI = dividend % divisor;
            }
        }
        else if (function == JALR) { 
            printf("JALR\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
        }
        else if (function == JR) {
            printf("JR\n");
            NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
        }
        else if (function == MFHI) { 
            printf("MFHI\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == MFLO) {
            printf("MFLO\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == MTHI) {
            printf("MTHI\n");
            NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == MTLO) { 
            printf("MTLO\n");
            NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == MULT) { 
            printf("MULT\n");
            long mult = CURRENT_STATE.REGS[rs] * CURRENT_STATE.REGS[rt];
            NEXT_STATE.LO = mult;
            NEXT_STATE.HI = mult >> 32;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == MULTU) { 
            printf("MULTU\n");
            unsigned int a = CURRENT_STATE.REGS[rs];
            unsigned int b = CURRENT_STATE.REGS[rt];
            long mult = a * b;
            NEXT_STATE.LO = mult;
            NEXT_STATE.HI = mult >> 32;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == NOR) { 
            printf("NOR\n");
            NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);   
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == OR) { 
            printf("OR\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];   
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SLL) { 
            printf("SLL\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SLLV) { 
            printf("SLLV\n");
            int shift = CURRENT_STATE.REGS[rs] & 0x1F; //five bit mask
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shift;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SLT) { 
            printf("SLT\n");
            if (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.REGS[rd] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rd] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SLTU) { 
            printf("SLTU\n");
            if ((unsigned)CURRENT_STATE.REGS[rs] < (unsigned)CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.REGS[rd] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rd] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SRA) { 
            printf("SRA\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SRAV) { 
            printf("SRAV\n");
            int shift = CURRENT_STATE.REGS[rs] & 0x1F; //five bit mask
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shift;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SRL) { 
            printf("SRL\n");
            NEXT_STATE.REGS[rd] = (unsigned)CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SRLV) { 
            printf("SRLV\n");
            int shift = CURRENT_STATE.REGS[rs] & 0x1F; //five bit mask
            NEXT_STATE.REGS[rd] = (unsigned)CURRENT_STATE.REGS[rt] >> sa;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SUB) { 
            printf("SUB\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SUBU) { 
            printf("SUBU\n");
            NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == SYSCALL) { 
            printf("SYSCALL\n");
            if (CURRENT_STATE.REGS[2] == 0x0A) {
                RUN_BIT = FALSE;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (function == XOR) { 
            printf("XOR\n");
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

        if (op == ADDI) { 
            printf("ADDI\n");
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imm;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == ADDIU) { 
            printf("ADDIU\n");
            unsigned int temp = CURRENT_STATE.REGS[rs] + imm;
            NEXT_STATE.REGS[rt] = temp;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == ANDI) { 
            printf("ANDI\n");
            NEXT_STATE.REGS[rt] = 0 | (imm & CURRENT_STATE.REGS[rs]);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == BEQ) { 
            printf("BEQ\n");
            if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target; 
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x1 && rt == 0x1) { //BGEZ
            printf("BGEZ\n");
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x1 && rt == 0x11) { //BGEZAL
            printf("BGEZAL\n");
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;

            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x7 && rt == 0) { //BGTZ
            printf("BGTZ\n");
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 0 && CURRENT_STATE.REGS[rs] != 0) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 && rt == 0) { //BLEZ
            printf("BLEZ\n");
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1 | CURRENT_STATE.REGS[rs] == 0) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x1 & rt == 0) { //BLTZ
            printf("BLTZ\n");
            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == 0x6 & rt == 0x10) { //BLTZAL
            printf("BLTZAL\n");
            NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;

            int shifted = CURRENT_STATE.REGS[rs] >> 31;
            if (shifted == 1) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4;
            }
        }
        else if (op == BNE) { 
            printf("BNE\n");
            if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
                NEXT_STATE.PC = CURRENT_STATE.PC + target;
            }
            else {
                NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
            }
        }
        else if (op == LB) { 
            printf("LB\n");
            NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
        }
        else if (op == LBU) { 
            printf("LBU\n");
            NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
        }
        else if (op == LH) {
            printf("LH\n");
            NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
        }
        else if (op == LHU) { 
            printf("LHU\n");
            NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
        }
        else if (op == LUI) { 
            printf("LUI\n");
            NEXT_STATE.REGS[rt] = imm << 16;
        }
        else if (op == LW) { 
            printf("LW\n");
            //NOT SURE ABOUT THIS ONE
            int vAddr = CURRENT_STATE.REGS[rs] + imm;
            NEXT_STATE.REGS[rt] = mem_read_32(vAddr);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == ORI) { 
            printf("ORI\n");
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | imm;
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == SB) {
            printf("SB\n");
            NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
        }
        else if (op == SH) {
            printf("SH\n");
            NEXT_STATE.PC = CURRENT_STATE.PC + 4; 
        }
        else if (op == SLTI) { 
            printf("SLTI\n");
            if (CURRENT_STATE.REGS[rs] < (short)imm) {
                NEXT_STATE.REGS[rt] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rt] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == SLTIU) {
            printf("SLTIU\n");
            if ((unsigned)CURRENT_STATE.REGS[rs] < (short)imm) {
                NEXT_STATE.REGS[rt] = 0x1;
            }
            else {
                NEXT_STATE.REGS[rt] = 0x0;
            }
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == SW) {
            printf("SW\n");
            unsigned int vAddr = CURRENT_STATE.REGS[rs] + imm;
            mem_write_32(vAddr, CURRENT_STATE.REGS[rt]);
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else if (op == XORI) {
            printf("XORI\n");
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ imm; 
            NEXT_STATE.PC = CURRENT_STATE.PC + 4;
        }
        else { //JUMPS
            unsigned int target = CURRENT_STATE.PC & 0x3FFFFFF; //mask of 26 1's

            if (op == J) {
            printf("J\n");
                NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | target << 2;
            }
            else if (op == JAL) {
            printf("JAL\n");
                NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;

                NEXT_STATE.PC = (CURRENT_STATE.PC & 0xF0000000) | target << 2;
            }
        }
    }
}

/* questions

*/