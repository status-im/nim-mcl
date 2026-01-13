# for gas
#ifdef __linux__
  #define PRE(x) x
  #define TYPE(x) .type x, @function
  #define SIZE(x) .size x, .-x
.section .note.GNU-stack,"",%progbits
#else
  #ifdef _WIN32
    #define PRE(x) x
  #else
    #define PRE(x) _ ## x
  #endif
  #define TYPE(x)
  #define SIZE(x)
#endif
.data
.balign 64
PRE(BN_P):
.quad 0x3c208c16d87cfd47,0x97816a916871ca8d,0xb85045b68181585d,0x30644e72e131a029

PRE(BN_ZERO):
.quad 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.quad 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

.text
.global PRE(mclx_Fr_preInv)
.balign 16

PRE(mclx_Fr_preInv):
TYPE(mclx_Fr_preInv)
   pushq  %rdi
   pushq  %rsi
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   subq $0x48, %rsp
   movq %rcx, %r10
   movq %rdx, %r11
   movq %r10, 0x18(%rsp)
   movq %r11, %rax
   movq (%rax), %r14
   movq 0x8(%rax), %r15
   movq 0x10(%rax), %rcx
   movq %rcx, (%rsp)
   movq 0x18(%rax), %rcx
   movq %rcx, 0x8(%rsp)
   leaq PRE(BN_P)(%rip), %rax
   movq (%rax), %rdx
   movq 0x8(%rax), %r11
   movq 0x10(%rax), %r10
   movq 0x18(%rax), %rcx
   movq %rcx, 0x10(%rsp)
   xorq %rax, %rax
   movq %rax, %r8
   movq %rax, %r9
   movq %rax, %rdi
   movq %rax, %rsi
   movq %rax, %rbx
   movq %rax, %rbp
   movq %rax, %r12
   movq %rax, %r13
   movl $0x1, %ebx
mclx_Fr_preInvL0:
   movq %r14, %rcx
   orq  %r15, %rcx
   orq  (%rsp), %rcx
   orq  0x8(%rsp), %rcx
   je  mclx_Fr_preInvL22
   testq  $0x1, %rdx
   je  mclx_Fr_preInvL4
   testq  $0x1, %r14
   je  mclx_Fr_preInvL2
   movq 0x8(%rsp), %rcx
   orq  0x10(%rsp), %rcx
   je  mclx_Fr_preInvL6
   movq 0x10(%rsp), %rcx
   cmpq %rcx, 0x8(%rsp)
   jb  mclx_Fr_preInvL3
   jne   mclx_Fr_preInvL1
   cmpq %r10, (%rsp)
   jb  mclx_Fr_preInvL3
   jne   mclx_Fr_preInvL1
   cmpq %r11, %r15
   jb  mclx_Fr_preInvL3
   jne   mclx_Fr_preInvL1
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL3
mclx_Fr_preInvL1:
   subq %rdx, %r14
   sbbq %r11, %r15
   sbbq %r10, (%rsp)
   movq 0x10(%rsp), %rcx
   sbbq %rcx, 0x8(%rsp)
   addq %r8, %rbx
   adcq %r9, %rbp
   adcq %rdi, %r12
   adcq %rsi, %r13
mclx_Fr_preInvL2:
   shrdq  $0x1, %r15, %r14
   movq (%rsp), %rcx
   shrdq  $0x1, %rcx, %r15
   movq 0x8(%rsp), %rcx
   shrdq  $0x1, %rcx, (%rsp)
   shrq 0x8(%rsp)
   addq %r8, %r8
   adcq %r9, %r9
   adcq %rdi, %rdi
   adcq %rsi, %rsi
   incq %rax
   jmp   mclx_Fr_preInvL0
mclx_Fr_preInvL3:
   subq %r14, %rdx
   sbbq %r15, %r11
   sbbq (%rsp), %r10
   movq 0x8(%rsp), %rcx
   sbbq %rcx, 0x10(%rsp)
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %rdi
   adcq %r13, %rsi
mclx_Fr_preInvL4:
   shrdq  $0x1, %r11, %rdx
   shrdq  $0x1, %r10, %r11
   movq 0x10(%rsp), %rcx
   shrdq  $0x1, %rcx, %r10
   shrq 0x10(%rsp)
   addq %rbx, %rbx
   adcq %rbp, %rbp
   adcq %r12, %r12
   adcq %r13, %r13
   incq %rax
   jmp   mclx_Fr_preInvL0
mclx_Fr_preInvL5:
   movq %r14, %rcx
   orq  %r15, %rcx
   orq  (%rsp), %rcx
   je  mclx_Fr_preInvL22
   testq  $0x1, %rdx
   je  mclx_Fr_preInvL10
   testq  $0x1, %r14
   je  mclx_Fr_preInvL8
mclx_Fr_preInvL6:
   movq (%rsp), %rcx
   orq  %r10, %rcx
   je  mclx_Fr_preInvL12
   cmpq %r10, (%rsp)
   jb  mclx_Fr_preInvL9
   jne   mclx_Fr_preInvL7
   cmpq %r11, %r15
   jb  mclx_Fr_preInvL9
   jne   mclx_Fr_preInvL7
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL9
mclx_Fr_preInvL7:
   subq %rdx, %r14
   sbbq %r11, %r15
   sbbq %r10, (%rsp)
   addq %r8, %rbx
   adcq %r9, %rbp
   adcq %rdi, %r12
   adcq %rsi, %r13
mclx_Fr_preInvL8:
   shrdq  $0x1, %r15, %r14
   movq (%rsp), %rcx
   shrdq  $0x1, %rcx, %r15
   shrq (%rsp)
   addq %r8, %r8
   adcq %r9, %r9
   adcq %rdi, %rdi
   adcq %rsi, %rsi
   incq %rax
   jmp   mclx_Fr_preInvL5
mclx_Fr_preInvL9:
   subq %r14, %rdx
   sbbq %r15, %r11
   sbbq (%rsp), %r10
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %rdi
   adcq %r13, %rsi
mclx_Fr_preInvL10:
   shrdq  $0x1, %r11, %rdx
   shrdq  $0x1, %r10, %r11
   shrq %r10
   addq %rbx, %rbx
   adcq %rbp, %rbp
   adcq %r12, %r12
   adcq %r13, %r13
   incq %rax
   jmp   mclx_Fr_preInvL5
mclx_Fr_preInvL11:
   movq %r14, %rcx
   orq  %r15, %rcx
   je  mclx_Fr_preInvL22
   testq  $0x1, %rdx
   je  mclx_Fr_preInvL16
   testq  $0x1, %r14
   je  mclx_Fr_preInvL14
mclx_Fr_preInvL12:
   movq %r15, %rcx
   orq  %r11, %rcx
   je  mclx_Fr_preInvL18
   cmpq %r11, %r15
   jb  mclx_Fr_preInvL15
   jne   mclx_Fr_preInvL13
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL15
mclx_Fr_preInvL13:
   subq %rdx, %r14
   sbbq %r11, %r15
   addq %r8, %rbx
   adcq %r9, %rbp
   adcq %rdi, %r12
   adcq %rsi, %r13
mclx_Fr_preInvL14:
   shrdq  $0x1, %r15, %r14
   shrq %r15
   addq %r8, %r8
   adcq %r9, %r9
   adcq %rdi, %rdi
   adcq %rsi, %rsi
   incq %rax
   jmp   mclx_Fr_preInvL11
mclx_Fr_preInvL15:
   subq %r14, %rdx
   sbbq %r15, %r11
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %rdi
   adcq %r13, %rsi
mclx_Fr_preInvL16:
   shrdq  $0x1, %r11, %rdx
   shrq %r11
   addq %rbx, %rbx
   adcq %rbp, %rbp
   adcq %r12, %r12
   adcq %r13, %r13
   incq %rax
   jmp   mclx_Fr_preInvL11
mclx_Fr_preInvL17:
   testq  %r14, %r14
   je  mclx_Fr_preInvL22
   testq  $0x1, %rdx
   je  mclx_Fr_preInvL21
   testq  $0x1, %r14
   je  mclx_Fr_preInvL19
mclx_Fr_preInvL18:
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL20
   subq %rdx, %r14
   addq %r8, %rbx
   adcq %r9, %rbp
   adcq %rdi, %r12
   adcq %rsi, %r13
mclx_Fr_preInvL19:
   shrq %r14
   addq %r8, %r8
   adcq %r9, %r9
   adcq %rdi, %rdi
   adcq %rsi, %rsi
   incq %rax
   jmp   mclx_Fr_preInvL17
mclx_Fr_preInvL20:
   subq %r14, %rdx
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %rdi
   adcq %r13, %rsi
mclx_Fr_preInvL21:
   shrq %rdx
   addq %rbx, %rbx
   adcq %rbp, %rbp
   adcq %r12, %r12
   adcq %r13, %r13
   incq %rax
   jmp   mclx_Fr_preInvL17
mclx_Fr_preInvL22:
   leaq PRE(BN_P)(%rip), %rbx
   movq 0x18(%rsp), %rdx
   movq (%rbx), %rcx
   subq %r8, %rcx
   movq %rcx, (%rdx)
   movq 0x8(%rbx), %rcx
   sbbq %r9, %rcx
   movq %rcx, 0x8(%rdx)
   movq 0x10(%rbx), %rcx
   sbbq %rdi, %rcx
   movq %rcx, 0x10(%rdx)
   movq 0x18(%rbx), %rcx
   sbbq %rsi, %rcx
   movq %rcx, 0x18(%rdx)
   jae   mclx_Fr_preInvL23
   movq (%rbx), %rcx
   addq %rcx, (%rdx)
   movq 0x8(%rbx), %rcx
   adcq %rcx, 0x8(%rdx)
   movq 0x10(%rbx), %rcx
   adcq %rcx, 0x10(%rdx)
   movq 0x18(%rbx), %rcx
   adcq %rcx, 0x18(%rdx)
mclx_Fr_preInvL23:
   addq $0x48, %rsp
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   popq %rsi
   popq %rdi
   retq
   nopw %cs:(%rax,%rax)
   nop
SIZE(mclx_Fr_preInv)

.global PRE(mclx_Fp_mul)
.balign 16

PRE(mclx_Fp_mul):
TYPE(mclx_Fp_mul)
   pushq  %rdi
   pushq  %rsi
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   movq %rdx, %r11
   callq  mclx_Fp_mulL0
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   popq %rsi
   popq %rdi
   retq
mclx_Fp_mulL0:
   vmovq  %rcx, %xmm0
   leaq PRE(BN_P)(%rip), %rcx
   vmovq  %r8, %xmm1
   movq (%r8), %r8
   movq %r8, %rdx
   mulxq  (%r11), %r10, %rdi
   mulxq  0x8(%r11), %rax, %rsi
   addq %rax, %rdi
   mulxq  0x10(%r11), %rax, %r8
   adcq %rax, %rsi
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r8
   adcq $0x0, %rdx
   movq %rdx, %r9
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %r10
   movq %rax, %r13
   movq %r13, %rdx
   mulxq  (%rcx), %rbx, %rbp
   mulxq  0x8(%rcx), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rcx), %rax, %r13
   adcq %rax, %r12
   mulxq  0x18(%rcx), %rax, %rdx
   adcq %rax, %r13
   adcq $0x0, %rdx
   addq %rbx, %r10
   adcq %rbp, %rdi
   adcq %r12, %rsi
   adcq %r8, %r13
   adcq %rdx, %r9
   vmovq  %xmm1, %r8
   movq 0x8(%r8), %r8
   movq %r8, %rdx
   mulxq  (%r11), %rbx, %rbp
   mulxq  0x8(%r11), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r11), %rax, %r8
   adcq %rax, %r12
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r8
   adcq $0x0, %rdx
   addq %rbx, %rdi
   adcq %rbp, %rsi
   adcq %r12, %r13
   adcq %r9, %r8
   adcq %rdx, %r10
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %rdi
   movq %rax, %r9
   movq %r9, %rdx
   mulxq  (%rcx), %rbx, %rbp
   mulxq  0x8(%rcx), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rcx), %rax, %r9
   adcq %rax, %r12
   mulxq  0x18(%rcx), %rax, %rdx
   adcq %rax, %r9
   adcq $0x0, %rdx
   addq %rbx, %rdi
   adcq %rbp, %rsi
   adcq %r12, %r13
   adcq %r8, %r9
   adcq %rdx, %r10
   vmovq  %xmm1, %r8
   movq 0x10(%r8), %r8
   movq %r8, %rdx
   mulxq  (%r11), %rbx, %rbp
   mulxq  0x8(%r11), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r11), %rax, %r8
   adcq %rax, %r12
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r8
   adcq $0x0, %rdx
   addq %rbx, %rsi
   adcq %rbp, %r13
   adcq %r12, %r9
   adcq %r10, %r8
   adcq %rdx, %rdi
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %rsi
   movq %rax, %r10
   movq %r10, %rdx
   mulxq  (%rcx), %rbx, %rbp
   mulxq  0x8(%rcx), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rcx), %rax, %r10
   adcq %rax, %r12
   mulxq  0x18(%rcx), %rax, %rdx
   adcq %rax, %r10
   adcq $0x0, %rdx
   addq %rbx, %rsi
   adcq %rbp, %r13
   adcq %r12, %r9
   adcq %r8, %r10
   adcq %rdx, %rdi
   vmovq  %xmm1, %r8
   movq 0x18(%r8), %r8
   movq %r8, %rdx
   mulxq  (%r11), %rbx, %rbp
   mulxq  0x8(%r11), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r11), %rax, %r8
   adcq %rax, %r12
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r8
   adcq $0x0, %rdx
   addq %rbx, %r13
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %rdi, %r8
   adcq %rdx, %rsi
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %r13
   movq %rax, %rdi
   movq %rdi, %rdx
   mulxq  (%rcx), %rbx, %rbp
   mulxq  0x8(%rcx), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rcx), %rax, %rdi
   adcq %rax, %r12
   mulxq  0x18(%rcx), %rax, %rdx
   adcq %rax, %rdi
   adcq $0x0, %rdx
   addq %rbx, %r13
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %r8, %rdi
   adcq %rdx, %rsi
   movq %r9, %rbx
   movq %r10, %rbp
   movq %rdi, %r12
   movq %rsi, %rdx
   subq (%rcx), %r9
   sbbq 0x8(%rcx), %r10
   sbbq 0x10(%rcx), %rdi
   sbbq 0x18(%rcx), %rsi
   cmovbq %rbx, %r9
   cmovbq %rbp, %r10
   cmovbq %r12, %rdi
   cmovbq %rdx, %rsi
   vmovq  %xmm0, %rcx
   movq %r9, (%rcx)
   movq %r10, 0x8(%rcx)
   movq %rdi, 0x10(%rcx)
   movq %rsi, 0x18(%rcx)
   retq
   nopw %cs:(%rax,%rax)
   nop
SIZE(mclx_Fp_mul)

.global PRE(mclx_Fp2_sqr)
.balign 16

PRE(mclx_Fp2_sqr):
TYPE(mclx_Fp2_sqr)
   pushq  %rdi
   pushq  %rsi
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   subq $0x78, %rsp
   movq %rdx, %r11
   movq %rcx, (%rsp)
   movq %r11, 0x8(%rsp)
   leaq 0x10(%rsp), %rcx
   movq 0x20(%r11), %r9
   movq 0x28(%r11), %r10
   movq 0x30(%r11), %rdi
   movq 0x38(%r11), %rsi
   shldq  $0x1, %rdi, %rsi
   shldq  $0x1, %r10, %rdi
   shldq  $0x1, %r9, %r10
   shlq %r9
   movq %r9, (%rcx)
   movq %r10, 0x8(%rcx)
   movq %rdi, 0x10(%rcx)
   movq %rsi, 0x18(%rcx)
   movq %rcx, %r11
   movq 0x8(%rsp), %r8
   callq mclx_Fp_mulL0
   movq 0x8(%rsp), %rcx
   movq (%rcx), %r9
   movq 0x8(%rcx), %r10
   movq 0x10(%rcx), %rdi
   movq 0x18(%rcx), %rsi
   movq 0x20(%rcx), %rbx
   movq 0x28(%rcx), %rbp
   movq 0x30(%rcx), %r12
   movq 0x38(%rcx), %r13
   movq %r9, %rax
   addq %rbx, %rax
   movq %rax, 0x30(%rsp)
   movq %r10, %rax
   adcq %rbp, %rax
   movq %rax, 0x38(%rsp)
   movq %rdi, %rax
   adcq %r12, %rax
   movq %rax, 0x40(%rsp)
   movq %rsi, %rax
   adcq %r13, %rax
   movq %rax, 0x48(%rsp)
   leaq PRE(BN_P)(%rip), %rax
   addq (%rax), %r9
   adcq 0x8(%rax), %r10
   adcq 0x10(%rax), %rdi
   adcq 0x18(%rax), %rsi
   subq %rbx, %r9
   sbbq %rbp, %r10
   sbbq %r12, %rdi
   sbbq %r13, %rsi
   movq %r9, 0x50(%rsp)
   movq %r10, 0x58(%rsp)
   movq %rdi, 0x60(%rsp)
   movq %rsi, 0x68(%rsp)
   movq (%rsp), %rcx
   leaq 0x30(%rsp), %r11
   leaq 0x50(%rsp), %r8
   callq mclx_Fp_mulL0
   movq (%rsp), %rcx
   movq 0x10(%rsp), %rax
   movq %rax, 0x20(%rcx)
   movq 0x18(%rsp), %rax
   movq %rax, 0x28(%rcx)
   movq 0x20(%rsp), %rax
   movq %rax, 0x30(%rcx)
   movq 0x28(%rsp), %rax
   movq %rax, 0x38(%rcx)
   addq $0x78, %rsp
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   popq %rsi
   popq %rdi
   retq
   nopw %cs:(%rax,%rax)
   nopl (%rax,%rax)
SIZE(mclx_Fp2_sqr)

.global PRE(mclx_Fp2dbl_mulPre)
.balign 16

PRE(mclx_Fp2dbl_mulPre):
TYPE(mclx_Fp2dbl_mulPre)
   pushq %rdi
   pushq %rsi
   pushq %rbx
   pushq %rbp
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15
   movq  %rdx, %r11
   callq  mclx_Fp2dbl_mulPreL0
   popq  %r15
   popq  %r14
   popq  %r13
   popq  %r12
   popq  %rbp
   popq  %rbx
   popq  %rsi
   popq  %rdi
   retq
mclx_Fp2dbl_mulPreL0:
   subq  $0x98, %rsp
   movq  %rcx, (%rsp)
   movq  %r11, 0x8(%rsp)
   movq  %r8, 0x10(%rsp)
   movq  (%r11), %rax
   addq  0x20(%r11), %rax
   movq  %rax, 0x18(%rsp)
   movq  0x8(%r11), %rax
   adcq  0x28(%r11), %rax
   movq  %rax, 0x20(%rsp)
   movq  0x10(%r11), %rax
   adcq  0x30(%r11), %rax
   movq  %rax, 0x28(%rsp)
   movq  0x18(%r11), %rax
   adcq  0x38(%r11), %rax
   movq  %rax, 0x30(%rsp)
   movq  (%r8), %rax
   addq  0x20(%r8), %rax
   movq  %rax, 0x38(%rsp)
   movq  0x8(%r8), %rax
   adcq  0x28(%r8), %rax
   movq  %rax, 0x40(%rsp)
   movq  0x10(%r8), %rax
   adcq  0x30(%r8), %rax
   movq  %rax, 0x48(%rsp)
   movq  0x18(%r8), %rax
   adcq  0x38(%r8), %rax
   movq  %rax, 0x50(%rsp)
   leaq  0x40(%rcx), %rcx
   movq  0x18(%rsp), %rdx
   mulxq 0x38(%rsp), %rax, %r9
   movq  %rax, (%rcx)
   mulxq 0x40(%rsp), %rax, %r10
   addq  %rax, %r9
   mulxq 0x48(%rsp), %rax, %rdi
   adcq  %rax, %r10
   mulxq 0x50(%rsp), %rax, %rsi
   adcq  %rax, %rdi
   adcq  $0x0, %rsi
   movq  0x20(%rsp), %r15
   movq  %r15, %rdx
   mulxq 0x38(%rsp), %rbp, %r12
   mulxq 0x40(%rsp), %rax, %r13
   addq  %rax, %r12
   mulxq 0x48(%rsp), %rax, %r15
   adcq  %rax, %r13
   mulxq 0x50(%rsp), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %rbp, %r9
   adcq  %r12, %r10
   adcq  %r13, %rdi
   adcq  %r15, %rsi
   adcq  $0x0, %rdx
   movq  %rdx, %r14
   movq  %r9, 0x8(%rcx)
   movq  0x28(%rsp), %r15
   movq  %r15, %rdx
   mulxq 0x38(%rsp), %rbx, %rbp
   mulxq 0x40(%rsp), %rax, %r12
   addq  %rax, %rbp
   mulxq 0x48(%rsp), %rax, %r15
   adcq  %rax, %r12
   mulxq 0x50(%rsp), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %rbx, %r10
   adcq  %rbp, %rdi
   adcq  %r12, %rsi
   adcq  %r15, %r14
   adcq  $0x0, %rdx
   movq  %rdx, %r13
   movq  %r10, 0x10(%rcx)
   movq  0x30(%rsp), %r15
   movq  %r15, %rdx
   mulxq 0x38(%rsp), %r10, %rbx
   mulxq 0x40(%rsp), %rax, %rbp
   addq  %rax, %rbx
   mulxq 0x48(%rsp), %rax, %r15
   adcq  %rax, %rbp
   mulxq 0x50(%rsp), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %r10, %rdi
   adcq  %rbx, %rsi
   adcq  %rbp, %r14
   adcq  %r15, %r13
   adcq  $0x0, %rdx
   movq  %rdi, 0x18(%rcx)
   movq  %rsi, 0x20(%rcx)
   movq  %r14, 0x28(%rcx)
   movq  %r13, 0x30(%rcx)
   movq  %rdx, 0x38(%rcx)
   movq  (%rsp), %rcx
   movq  0x8(%rsp), %r11
   movq  0x10(%rsp), %r8
   movq  (%r11), %rdx
   mulxq (%r8), %rax, %r9
   movq  %rax, (%rcx)
   mulxq 0x8(%r8), %rax, %r10
   addq  %rax, %r9
   mulxq 0x10(%r8), %rax, %rdi
   adcq  %rax, %r10
   mulxq 0x18(%r8), %rax, %rsi
   adcq  %rax, %rdi
   adcq  $0x0, %rsi
   movq  0x8(%r11), %r15
   movq  %r15, %rdx
   mulxq (%r8), %rbp, %r12
   mulxq 0x8(%r8), %rax, %r13
   addq  %rax, %r12
   mulxq 0x10(%r8), %rax, %r15
   adcq  %rax, %r13
   mulxq 0x18(%r8), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %rbp, %r9
   adcq  %r12, %r10
   adcq  %r13, %rdi
   adcq  %r15, %rsi
   adcq  $0x0, %rdx
   movq  %rdx, %r14
   movq  %r9, 0x8(%rcx)
   movq  0x10(%r11), %r15
   movq  %r15, %rdx
   mulxq (%r8), %rbx, %rbp
   mulxq 0x8(%r8), %rax, %r12
   addq  %rax, %rbp
   mulxq 0x10(%r8), %rax, %r15
   adcq  %rax, %r12
   mulxq 0x18(%r8), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %rbx, %r10
   adcq  %rbp, %rdi
   adcq  %r12, %rsi
   adcq  %r15, %r14
   adcq  $0x0, %rdx
   movq  %rdx, %r13
   movq  %r10, 0x10(%rcx)
   movq  0x18(%r11), %r15
   movq  %r15, %rdx
   mulxq (%r8), %r10, %rbx
   mulxq 0x8(%r8), %rax, %rbp
   addq  %rax, %rbx
   mulxq 0x10(%r8), %rax, %r15
   adcq  %rax, %rbp
   mulxq 0x18(%r8), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %r10, %rdi
   adcq  %rbx, %rsi
   adcq  %rbp, %r14
   adcq  %r15, %r13
   adcq  $0x0, %rdx
   movq  %rdi, 0x18(%rcx)
   movq  %rsi, 0x20(%rcx)
   movq  %r14, 0x28(%rcx)
   movq  %r13, 0x30(%rcx)
   movq  %rdx, 0x38(%rcx)
   movq  0x8(%rsp), %r11
   addq  $0x20, %r11
   movq  0x10(%rsp), %r8
   addq  $0x20, %r8
   movq  (%r11), %rdx
   mulxq (%r8), %rax, %r9
   movq  %rax, 0x58(%rsp)
   mulxq 0x8(%r8), %rax, %r10
   addq  %rax, %r9
   mulxq 0x10(%r8), %rax, %rdi
   adcq  %rax, %r10
   mulxq 0x18(%r8), %rax, %rsi
   adcq  %rax, %rdi
   adcq  $0x0, %rsi
   movq  0x8(%r11), %r15
   movq  %r15, %rdx
   mulxq (%r8), %rbp, %r12
   mulxq 0x8(%r8), %rax, %r13
   addq  %rax, %r12
   mulxq 0x10(%r8), %rax, %r15
   adcq  %rax, %r13
   mulxq 0x18(%r8), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %rbp, %r9
   adcq  %r12, %r10
   adcq  %r13, %rdi
   adcq  %r15, %rsi
   adcq  $0x0, %rdx
   movq  %rdx, %r14
   movq  %r9, 0x60(%rsp)
   movq  0x10(%r11), %r15
   movq  %r15, %rdx
   mulxq (%r8), %rbx, %rbp
   mulxq 0x8(%r8), %rax, %r12
   addq  %rax, %rbp
   mulxq 0x10(%r8), %rax, %r15
   adcq  %rax, %r12
   mulxq 0x18(%r8), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %rbx, %r10
   adcq  %rbp, %rdi
   adcq  %r12, %rsi
   adcq  %r15, %r14
   adcq  $0x0, %rdx
   movq  %rdx, %r13
   movq  %r10, 0x68(%rsp)
   movq  0x18(%r11), %r15
   movq  %r15, %rdx
   mulxq (%r8), %r10, %rbx
   mulxq 0x8(%r8), %rax, %rbp
   addq  %rax, %rbx
   mulxq 0x10(%r8), %rax, %r15
   adcq  %rax, %rbp
   mulxq 0x18(%r8), %rax, %rdx
   adcq  %rax, %r15
   adcq  $0x0, %rdx
   addq  %r10, %rdi
   adcq  %rbx, %rsi
   adcq  %rbp, %r14
   adcq  %r15, %r13
   adcq  $0x0, %rdx
   movq  %rdi, 0x70(%rsp)
   movq  %rsi, 0x78(%rsp)
   movq  %r14, 0x80(%rsp)
   movq  %r13, 0x88(%rsp)
   movq  %rdx, 0x90(%rsp)
   movq  (%rsp), %rcx
   movq  0x40(%rcx), %r9
   movq  0x48(%rcx), %r10
   movq  0x50(%rcx), %rdi
   movq  0x58(%rcx), %rsi
   movq  0x60(%rcx), %rbx
   movq  0x68(%rcx), %rbp
   movq  0x70(%rcx), %r12
   movq  0x78(%rcx), %r13
   subq  (%rcx), %r9
   sbbq  0x8(%rcx), %r10
   sbbq  0x10(%rcx), %rdi
   sbbq  0x18(%rcx), %rsi
   sbbq  0x20(%rcx), %rbx
   sbbq  0x28(%rcx), %rbp
   sbbq  0x30(%rcx), %r12
   sbbq  0x38(%rcx), %r13
   subq  0x58(%rsp), %r9
   sbbq  0x60(%rsp), %r10
   sbbq  0x68(%rsp), %rdi
   sbbq  0x70(%rsp), %rsi
   sbbq  0x78(%rsp), %rbx
   sbbq  0x80(%rsp), %rbp
   sbbq  0x88(%rsp), %r12
   sbbq  0x90(%rsp), %r13
   movq  %r9, 0x40(%rcx)
   movq  %r10, 0x48(%rcx)
   movq  %rdi, 0x50(%rcx)
   movq  %rsi, 0x58(%rcx)
   movq  %rbx, 0x60(%rcx)
   movq  %rbp, 0x68(%rcx)
   movq  %r12, 0x70(%rcx)
   movq  %r13, 0x78(%rcx)
   movq  (%rcx), %rax
   subq  0x58(%rsp), %rax
   movq  %rax, (%rcx)
   movq  0x8(%rcx), %rax
   sbbq  0x60(%rsp), %rax
   movq  %rax, 0x8(%rcx)
   movq  0x10(%rcx), %rax
   sbbq  0x68(%rsp), %rax
   movq  %rax, 0x10(%rcx)
   movq  0x18(%rcx), %rax
   sbbq  0x70(%rsp), %rax
   movq  %rax, 0x18(%rcx)
   movq  0x20(%rcx), %r9
   movq  0x28(%rcx), %r10
   movq  0x30(%rcx), %rdi
   movq  0x38(%rcx), %rsi
   sbbq  0x78(%rsp), %r9
   sbbq  0x80(%rsp), %r10
   sbbq  0x88(%rsp), %rdi
   sbbq  0x90(%rsp), %rsi
   leaq PRE(BN_ZERO)(%rip), %rax
   leaq PRE(BN_P)(%rip), %rbx
   cmovbq  %rbx, %rax
   addq  (%rax), %r9
   adcq  0x8(%rax), %r10
   adcq  0x10(%rax), %rdi
   adcq  0x18(%rax), %rsi
   movq  %r9, 0x20(%rcx)
   movq  %r10, 0x28(%rcx)
   movq  %rdi, 0x30(%rcx)
   movq  %rsi, 0x38(%rcx)
   addq  $0x98, %rsp
   retq
   nop
SIZE(mclx_Fp2dbl_mulPre)

.global PRE(mclx_Fpdbl_mod)
.balign 16

PRE(mclx_Fpdbl_mod):
TYPE(mclx_Fpdbl_mod)
   pushq %rdi
   pushq %rsi
   pushq %rbx
   pushq %rbp
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15
   movq  %rdx, %r11
   callq mclx_Fpdbl_modL0
   popq  %r15
   popq  %r14
   popq  %r13
   popq  %r12
   popq  %rbp
   popq  %rbx
   popq  %rsi
   popq  %rdi
   retq
mclx_Fpdbl_modL0:
   leaq PRE(BN_P)(%rip), %r13
   xorq  %rbp, %rbp
   movq  (%r11), %r9
   movq  0x8(%r11), %r10
   movq  0x10(%r11), %rdi
   movq  0x18(%r11), %rsi
   movabsq $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq %r9, %rdx
   xorq  %rax, %rax
   mulxq (%r13), %rax, %r12
   adoxq %rax, %r9
   movq  0x20(%r11), %rbx
   adcxq %r12, %r10
   mulxq 0x8(%r13), %rax, %r12
   adoxq %rax, %r10
   adcxq %r12, %rdi
   mulxq 0x10(%r13), %rax, %r12
   adoxq %rax, %rdi
   adcxq %r12, %rsi
   mulxq 0x18(%r13), %rax, %r12
   adoxq %rax, %rsi
   adoxq %r9, %r12
   adcxq %r12, %rbx
   setb  %bpl
   movabsq $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq %r10, %rdx
   xorq  %rax, %rax
   mulxq (%r13), %rax, %r12
   adoxq %rax, %r10
   movq  0x28(%r11), %r9
   adcxq %r12, %rdi
   mulxq 0x8(%r13), %rax, %r12
   adoxq %rax, %rdi
   adcxq %r12, %rsi
   mulxq 0x10(%r13), %rax, %r12
   adoxq %rax, %rsi
   adcxq %r12, %rbx
   mulxq 0x18(%r13), %rax, %r12
   adoxq %rax, %rbx
   adoxq %r10, %r12
   adoxq %rbp, %r12
   adcxq %r12, %r9
   setb  %bpl
   movabsq $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq %rdi, %rdx
   xorq  %rax, %rax
   mulxq (%r13), %rax, %r12
   adoxq %rax, %rdi
   movq  0x30(%r11), %r10
   adcxq %r12, %rsi
   mulxq 0x8(%r13), %rax, %r12
   adoxq %rax, %rsi
   adcxq %r12, %rbx
   mulxq 0x10(%r13), %rax, %r12
   adoxq %rax, %rbx
   adcxq %r12, %r9
   mulxq 0x18(%r13), %rax, %r12
   adoxq %rax, %r9
   adoxq %rdi, %r12
   adoxq %rbp, %r12
   adcxq %r12, %r10
   setb  %bpl
   movabsq $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq %rsi, %rdx
   xorq  %rax, %rax
   mulxq (%r13), %rax, %r12
   adoxq %rax, %rsi
   movq  0x38(%r11), %rdi
   adcxq %r12, %rbx
   mulxq 0x8(%r13), %rax, %r12
   adoxq %rax, %rbx
   adcxq %r12, %r9
   mulxq 0x10(%r13), %rax, %r12
   adoxq %rax, %r9
   adcxq %r12, %r10
   mulxq 0x18(%r13), %rax, %r12
   adoxq %rax, %r10
   adoxq %rsi, %r12
   adoxq %rbp, %r12
   adcxq %r12, %rdi
   movq  %rbx, %rsi
   movq  %r9, %rbp
   movq  %r10, %r12
   movq  %rdi, %rdx
   subq  (%r13), %rbx
   sbbq  0x8(%r13), %r9
   sbbq  0x10(%r13), %r10
   sbbq  0x18(%r13), %rdi
   cmovbq  %rsi, %rbx
   cmovbq  %rbp, %r9
   cmovbq  %r12, %r10
   cmovbq  %rdx, %rdi
   movq  %rbx, (%rcx)
   movq  %r9, 0x8(%rcx)
   movq  %r10, 0x10(%rcx)
   movq  %rdi, 0x18(%rcx)
   retq
SIZE(mclx_Fpdbl_mod)

.global PRE(mclx_Fp2_mul)
.balign 16

PRE(mclx_Fp2_mul):
TYPE(mclx_Fp2_mul)
   pushq %rdi
   pushq %rsi
   pushq %rbx
   pushq %rbp
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15
   subq  $0x88, %rsp
   movq  %rdx, %r11
   movq  %rcx, (%rsp)
   leaq  0x8(%rsp), %rcx
   callq mclx_Fp2dbl_mulPreL0
   movq  (%rsp), %rcx
   leaq  0x8(%rsp), %r11
   callq mclx_Fpdbl_modL0
   movq  (%rsp), %rcx
   addq  $0x20, %rcx
   leaq  0x48(%rsp), %r11
   callq mclx_Fpdbl_modL0
   addq  $0x88, %rsp
   popq  %r15
   popq  %r14
   popq  %r13
   popq  %r12
   popq  %rbp
   popq  %rbx
   popq  %rsi
   popq  %rdi
   retq
SIZE(mclx_Fp2_mul)

mclx_Fpdbl_mulPreL0:
   movq (%r11), %rdx
   mulxq  (%r8), %rax, %r9
   movq %rax, (%rcx)
   mulxq  0x8(%r8), %rax, %r10
   addq %rax, %r9
   mulxq  0x10(%r8), %rax, %rdi
   adcq %rax, %r10
   mulxq  0x18(%r8), %rax, %rsi
   adcq %rax, %rdi
   adcq $0x0, %rsi
   movq 0x8(%r11), %r15
   movq %r15, %rdx
   mulxq  (%r8), %rbp, %r12
   mulxq  0x8(%r8), %rax, %r13
   addq %rax, %r12
   mulxq  0x10(%r8), %rax, %r15
   adcq %rax, %r13
   mulxq  0x18(%r8), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbp, %r9
   adcq %r12, %r10
   adcq %r13, %rdi
   adcq %r15, %rsi
   adcq $0x0, %rdx
   movq %rdx, %r14
   movq %r9, 0x8(%rcx)
   movq 0x10(%r11), %r15
   movq %r15, %rdx
   mulxq  (%r8), %rbx, %rbp
   mulxq  0x8(%r8), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r8), %rax, %r15
   adcq %rax, %r12
   mulxq  0x18(%r8), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbx, %r10
   adcq %rbp, %rdi
   adcq %r12, %rsi
   adcq %r15, %r14
   adcq $0x0, %rdx
   movq %rdx, %r13
   movq %r10, 0x10(%rcx)
   movq 0x18(%r11), %r15
   movq %r15, %rdx
   mulxq  (%r8), %r10, %rbx
   mulxq  0x8(%r8), %rax, %rbp
   addq %rax, %rbx
   mulxq  0x10(%r8), %rax, %r15
   adcq %rax, %rbp
   mulxq  0x18(%r8), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %r10, %rdi
   adcq %rbx, %rsi
   adcq %rbp, %r14
   adcq %r15, %r13
   adcq $0x0, %rdx
   movq %rdi, 0x18(%rcx)
   movq %rsi, 0x20(%rcx)
   movq %r14, 0x28(%rcx)
   movq %r13, 0x30(%rcx)
   movq %rdx, 0x38(%rcx)
   retq
   nopw (%rax,%rax)

.global PRE(mclx_Fp2dbl_sqrPre)
.balign 16

PRE(mclx_Fp2dbl_sqrPre):
TYPE(mclx_Fp2dbl_sqrPre)
   pushq %rdi
   pushq %rsi
   pushq %rbx
   pushq %rbp
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15
   subq  $0x58, %rsp
   movq  %rdx, %r11
   movq  %rcx, (%rsp)
   movq  %r11, 0x8(%rsp)
   movq  0x20(%r11), %rbx
   movq  0x28(%r11), %rbp
   movq  0x30(%r11), %r12
   movq  0x38(%r11), %r13
   movq  %rbx, %rax
   addq  %rax, %rax
   movq  %rax, 0x10(%rsp)
   movq  %rbp, %rax
   adcq  %rax, %rax
   movq  %rax, 0x18(%rsp)
   movq  %r12, %rax
   adcq  %rax, %rax
   movq  %rax, 0x20(%rsp)
   movq  %r13, %rax
   adcq  %rax, %rax
   movq  %rax, 0x28(%rsp)
   movq  (%r11), %r9
   movq  0x8(%r11), %r10
   movq  0x10(%r11), %rdi
   movq  0x18(%r11), %rsi
   addq  %rbx, %r9
   adcq  %rbp, %r10
   adcq  %r12, %rdi
   adcq  %r13, %rsi
   movq  %r9, 0x30(%rsp)
   movq  %r10, 0x38(%rsp)
   movq  %rdi, 0x40(%rsp)
   movq  %rsi, 0x48(%rsp)
   movq  (%rsp), %rcx
   addq  $0x40, %rcx
   leaq  0x10(%rsp), %r11
   movq  0x8(%rsp), %r8
   callq  mclx_Fpdbl_mulPreL0
   movq  0x8(%rsp), %rcx
   movq  (%rcx), %r9
   movq  0x8(%rcx), %r10
   movq  0x10(%rcx), %rdi
   movq  0x18(%rcx), %rsi
   subq  0x20(%rcx), %r9
   sbbq  0x28(%rcx), %r10
   sbbq  0x30(%rcx), %rdi
   sbbq  0x38(%rcx), %rsi
   leaq PRE(BN_ZERO)(%rip), %rax
   leaq PRE(BN_P)(%rip), %rbx
   cmovbq  %rbx, %rax
   addq  (%rax), %r9
   adcq  0x8(%rax), %r10
   adcq  0x10(%rax), %rdi
   adcq  0x18(%rax), %rsi
   movq  %r9, 0x10(%rsp)
   movq  %r10, 0x18(%rsp)
   movq  %rdi, 0x20(%rsp)
   movq  %rsi, 0x28(%rsp)
   movq  (%rsp), %rcx
   leaq  0x10(%rsp), %r11
   leaq  0x30(%rsp), %r8
   callq  mclx_Fpdbl_mulPreL0
   addq  $0x58, %rsp
   popq  %r15
   popq  %r14
   popq  %r13
   popq  %r12
   popq  %rbp
   popq  %rbx
   popq  %rsi
   popq  %rdi
   retq
   nopl  (%rax,%rax)
SIZE(mclx_Fp2dbl_sqrPre)
