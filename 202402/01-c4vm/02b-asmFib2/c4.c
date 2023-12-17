// c4.c - C in four functions

// char, int, and pointer types
// if, while, return, and expression statements
// just enough features to allow self-compilation and a bit more

// Written by Robert Swierczek
// 修改者: 陳鍾誠 (模組化並加上中文註解)

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#define int long long // 64 bit 電腦

int *e;  // current position in emitted code (e: 目前機器碼指標, le: 上一行機器碼指標)
int debug = 1;

// opcodes (機器碼的 op)
enum { LLA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT };

int run(int *pc, int *bp, int *sp) { // 虛擬機 => pc: 程式計數器, sp: 堆疊暫存器, bp: 框架暫存器
  int a, cycle; // a: 累積器, cycle: 執行指令數
  int i, *t;    // temps

  cycle = 0;
  while (1) {
    i = *pc++; ++cycle;
    if (debug) {
      printf("%d> %.4s", cycle,
        &"LLA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
         "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
         "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[i * 5]);
      if (i <= ADJ) printf(" %d\n", *pc); else printf("\n");
    }
    if      (i == LLA) a = (int)(bp + *pc++);                             // load local address 載入區域變數
    else if (i == IMM) a = *pc++;                                         // load global address or immediate 載入全域變數或立即值
    else if (i == JMP) pc = (int *)*pc;                                   // jump               躍躍指令
    else if (i == JSR) { *--sp = (int)(pc + 1); pc = (int *)*pc; }        // jump to subroutine 跳到副程式
    else if (i == BZ)  pc = a ? pc + 1 : (int *)*pc;                      // branch if zero     if (a==0) goto m[pc]
    else if (i == BNZ) pc = a ? (int *)*pc : pc + 1;                      // branch if not zero if (a!=0) goto m[pc]
    else if (i == ENT) { *--sp = (int)bp; bp = sp; sp = sp - *pc++; }     // enter subroutine   進入副程式
    else if (i == ADJ) sp = sp + *pc++;                                   // stack adjust       調整堆疊
    else if (i == LEV) { sp = bp; bp = (int *)*sp++; pc = (int *)*sp++; } // leave subroutine   離開副程式
    else if (i == LI)  a = *(int *)a;                                     // load int           載入整數
    else if (i == LC)  a = *(char *)a;                                    // load char          載入字元
    else if (i == SI)  *(int *)*sp++ = a;                                 // store int          儲存整數
    else if (i == SC)  a = *(char *)*sp++ = a;                            // store char         儲存字元
    else if (i == PSH) *--sp = a;                                         // push               推入堆疊

    else if (i == OR)  a = *sp++ |  a; // a = a OR *sp
    else if (i == XOR) a = *sp++ ^  a; // a = a XOR *sp
    else if (i == AND) a = *sp++ &  a; // ...
    else if (i == EQ)  a = *sp++ == a;
    else if (i == NE)  a = *sp++ != a;
    else if (i == LT)  a = *sp++ <  a;
    else if (i == GT)  a = *sp++ >  a;
    else if (i == LE)  a = *sp++ <= a;
    else if (i == GE)  a = *sp++ >= a;
    else if (i == SHL) a = *sp++ << a;
    else if (i == SHR) a = *sp++ >> a;
    else if (i == ADD) a = *sp++ +  a;
    else if (i == SUB) a = *sp++ -  a;
    else if (i == MUL) a = *sp++ *  a;
    else if (i == DIV) a = *sp++ /  a;
    else if (i == MOD) a = *sp++ %  a;

    else if (i == OPEN) a = open((char *)sp[1], *sp); // 開檔
    else if (i == READ) a = read(sp[2], (char *)sp[1], *sp); // 讀檔
    else if (i == CLOS) a = close(*sp); // 關檔
    else if (i == PRTF) { t = sp + pc[1]; a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]); } // printf("....", a, b, c, d, e)
    else if (i == MALC) a = (int)malloc(*sp); // 分配記憶體
    else if (i == FREE) free((void *)*sp); // 釋放記憶體
    else if (i == MSET) a = (int)memset((char *)sp[2], sp[1], *sp); // 設定記憶體
    else if (i == MCMP) a = memcmp((char *)sp[2], (char *)sp[1], *sp); // 比較記憶體
    else if (i == EXIT) { printf("exit(%d) cycle = %d\n", *sp, cycle); return *sp; } // EXIT 離開
    else { printf("unknown instruction = %d! cycle = %d\n", i, cycle); return -1; } // 錯誤處理
  }
}

#define E1(op) *e++ = op
#define E2(op, arg) *e++ = op; *e++ = (int) arg
int main(int argc, char **argv) // 主程式
{
  int *pc, *bp, *sp, poolsz, t, *fib, *loc;

  poolsz = 256*1024; // arbitrary size
  if (!(e = malloc(poolsz))) { printf("could not malloc(%d) text area\n", poolsz); return -1; } // 程式段
  if (!(sp = malloc(poolsz))) { printf("could not malloc(%d) stack area\n", poolsz); return -1; }  // 堆疊段

  memset(e, 0, poolsz);

// 3: int f(int n) {
// 4:   if (n<=0) return 0;
  fib = e;
  E2(ENT, 0);
  E2(LLA, 2);
  E1(LI);
  E1(PSH);
  E2(IMM, 0);
  E1(LE);
  E2(BZ, 0); loc=e-1;
  E2(IMM, 0);
  E1(LEV);
// 5:   if (n==1) return 1;
  *loc = (int) e;
  E2(LLA, 2);
  E1(LI);
  E1(PSH);
  E2(IMM, 1);
  E1(EQ);
  E2(BZ, 0); loc=e-1;
  E2(IMM,1);
  E1(LEV);
// 6:   return f(n-1) + f(n-2);
  *loc = (int) e; 
  E2(LLA, 2);
  E1(LI);
  E1(PSH);
  E2(IMM, 1);
  E1(SUB);
  E1(PSH);
  E2(JSR, fib);
  E2(ADJ, 1);
  E1(PSH);
  E2(LLA, 2);
  E1(LI);
  E1(PSH);
  E2(IMM,2);
  E1(SUB);
  E1(PSH);
  E2(JSR, fib);
  E2(ADJ, 1);
  E1(ADD);
  E1(LEV);
// 7: }
//    LEV
  E1(LEV);
// 8:
// 9: int main() {
// 10:   printf("f(7)=%d\n", f(7));
  pc = e;
  E2(ENT, 0);
  E2(IMM, "f(7)=%d\n");
  E1(PSH);
  E2(IMM, 7);
  E1(PSH);
  E2(JSR, fib);
  E2(ADJ, 1);
  E1(PSH);
  E1(PRTF);
  E2(ADJ,2);
// 11: }
  E1(LEV);

  // setup stack
  bp = sp = (int *)((int)sp + poolsz);
  *--sp = EXIT; // call exit if main returns
  *--sp = PSH; t = (int) sp;
  *--sp = argc;
  *--sp = (int)argv;
  *--sp = (int)t;
  return run(pc, bp, sp);
}