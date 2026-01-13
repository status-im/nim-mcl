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
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   subq $0x48, %rsp
   movq %rdi, 0x18(%rsp)
   movq %rsi, %rax
   movq (%rax), %r14
   movq 0x8(%rax), %r15
   movq 0x10(%rax), %rcx
   movq %rcx, (%rsp)
   movq 0x18(%rax), %rcx
   movq %rcx, 0x8(%rsp)
   leaq PRE(BN_P)(%rip), %rax
   movq (%rax), %rdx
   movq 0x8(%rax), %rsi
   movq 0x10(%rax), %rdi
   movq 0x18(%rax), %rcx
   movq %rcx, 0x10(%rsp)
   xorq %rax, %rax
   movq %rax, %r11
   movq %rax, %r10
   movq %rax, %r8
   movq %rax, %r9
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
   cmpq %rdi, (%rsp)
   jb  mclx_Fr_preInvL3
   jne   mclx_Fr_preInvL1
   cmpq %rsi, %r15
   jb  mclx_Fr_preInvL3
   jne   mclx_Fr_preInvL1
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL3
mclx_Fr_preInvL1:
   subq %rdx, %r14
   sbbq %rsi, %r15
   sbbq %rdi, (%rsp)
   movq 0x10(%rsp), %rcx
   sbbq %rcx, 0x8(%rsp)
   addq %r11, %rbx
   adcq %r10, %rbp
   adcq %r8, %r12
   adcq %r9, %r13
mclx_Fr_preInvL2:
   shrdq  $0x1, %r15, %r14
   movq (%rsp), %rcx
   shrdq  $0x1, %rcx, %r15
   movq 0x8(%rsp), %rcx
   shrdq  $0x1, %rcx, (%rsp)
   shrq 0x8(%rsp)
   addq %r11, %r11
   adcq %r10, %r10
   adcq %r8, %r8
   adcq %r9, %r9
   incq %rax
   jmp   mclx_Fr_preInvL0
mclx_Fr_preInvL3:
   subq %r14, %rdx
   sbbq %r15, %rsi
   sbbq (%rsp), %rdi
   movq 0x8(%rsp), %rcx
   sbbq %rcx, 0x10(%rsp)
   addq %rbx, %r11
   adcq %rbp, %r10
   adcq %r12, %r8
   adcq %r13, %r9
mclx_Fr_preInvL4:
   shrdq  $0x1, %rsi, %rdx
   shrdq  $0x1, %rdi, %rsi
   movq 0x10(%rsp), %rcx
   shrdq  $0x1, %rcx, %rdi
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
   orq  %rdi, %rcx
   je  mclx_Fr_preInvL12
   cmpq %rdi, (%rsp)
   jb  mclx_Fr_preInvL9
   jne   mclx_Fr_preInvL7
   cmpq %rsi, %r15
   jb  mclx_Fr_preInvL9
   jne   mclx_Fr_preInvL7
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL9
mclx_Fr_preInvL7:
   subq %rdx, %r14
   sbbq %rsi, %r15
   sbbq %rdi, (%rsp)
   addq %r11, %rbx
   adcq %r10, %rbp
   adcq %r8, %r12
   adcq %r9, %r13
mclx_Fr_preInvL8:
   shrdq  $0x1, %r15, %r14
   movq (%rsp), %rcx
   shrdq  $0x1, %rcx, %r15
   shrq (%rsp)
   addq %r11, %r11
   adcq %r10, %r10
   adcq %r8, %r8
   adcq %r9, %r9
   incq %rax
   jmp   mclx_Fr_preInvL5
mclx_Fr_preInvL9:
   subq %r14, %rdx
   sbbq %r15, %rsi
   sbbq (%rsp), %rdi
   addq %rbx, %r11
   adcq %rbp, %r10
   adcq %r12, %r8
   adcq %r13, %r9
mclx_Fr_preInvL10:
   shrdq  $0x1, %rsi, %rdx
   shrdq  $0x1, %rdi, %rsi
   shrq %rdi
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
   orq  %rsi, %rcx
   je  mclx_Fr_preInvL18
   cmpq %rsi, %r15
   jb  mclx_Fr_preInvL15
   jne   mclx_Fr_preInvL13
   cmpq %rdx, %r14
   jb  mclx_Fr_preInvL15
mclx_Fr_preInvL13:
   subq %rdx, %r14
   sbbq %rsi, %r15
   addq %r11, %rbx
   adcq %r10, %rbp
   adcq %r8, %r12
   adcq %r9, %r13
mclx_Fr_preInvL14:
   shrdq  $0x1, %r15, %r14
   shrq %r15
   addq %r11, %r11
   adcq %r10, %r10
   adcq %r8, %r8
   adcq %r9, %r9
   incq %rax
   jmp   mclx_Fr_preInvL11
mclx_Fr_preInvL15:
   subq %r14, %rdx
   sbbq %r15, %rsi
   addq %rbx, %r11
   adcq %rbp, %r10
   adcq %r12, %r8
   adcq %r13, %r9
mclx_Fr_preInvL16:
   shrdq  $0x1, %rsi, %rdx
   shrq %rsi
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
   addq %r11, %rbx
   adcq %r10, %rbp
   adcq %r8, %r12
   adcq %r9, %r13
mclx_Fr_preInvL19:
   shrq %r14
   addq %r11, %r11
   adcq %r10, %r10
   adcq %r8, %r8
   adcq %r9, %r9
   incq %rax
   jmp   mclx_Fr_preInvL17
mclx_Fr_preInvL20:
   subq %r14, %rdx
   addq %rbx, %r11
   adcq %rbp, %r10
   adcq %r12, %r8
   adcq %r13, %r9
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
   subq %r11, %rcx
   movq %rcx, (%rdx)
   movq 0x8(%rbx), %rcx
   sbbq %r10, %rcx
   movq %rcx, 0x8(%rdx)
   movq 0x10(%rbx), %rcx
   sbbq %r8, %rcx
   movq %rcx, 0x10(%rdx)
   movq 0x18(%rbx), %rcx
   sbbq %r9, %rcx
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
   retq
   nop
   nopl (%rax,%rax)
SIZE(mclx_Fr_preInv)

.global PRE(mclx_Fp_mul)
.balign 16

PRE(mclx_Fp_mul):
TYPE(mclx_Fp_mul)
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
   retq
mclx_Fp_mulL0:
   vmovq  %rdi, %xmm0
   leaq PRE(BN_P)(%rip), %rdi
   vmovq  %r11, %xmm1
   movq (%r11), %r11
   movq %r11, %rdx
   mulxq  (%rsi), %r8, %r9
   mulxq  0x8(%rsi), %rax, %r10
   addq %rax, %r9
   mulxq  0x10(%rsi), %rax, %r11
   adcq %rax, %r10
   mulxq  0x18(%rsi), %rax, %rdx
   adcq %rax, %r11
   adcq $0x0, %rdx
   movq %rdx, %rcx
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %r8
   movq %rax, %r13
   movq %r13, %rdx
   mulxq  (%rdi), %rbx, %rbp
   mulxq  0x8(%rdi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rdi), %rax, %r13
   adcq %rax, %r12
   mulxq  0x18(%rdi), %rax, %rdx
   adcq %rax, %r13
   adcq $0x0, %rdx
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %r11, %r13
   adcq %rdx, %rcx
   vmovq  %xmm1, %r11
   movq 0x8(%r11), %r11
   movq %r11, %rdx
   mulxq  (%rsi), %rbx, %rbp
   mulxq  0x8(%rsi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rsi), %rax, %r11
   adcq %rax, %r12
   mulxq  0x18(%rsi), %rax, %rdx
   adcq %rax, %r11
   adcq $0x0, %rdx
   addq %rbx, %r9
   adcq %rbp, %r10
   adcq %r12, %r13
   adcq %rcx, %r11
   adcq %rdx, %r8
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %r9
   movq %rax, %rcx
   movq %rcx, %rdx
   mulxq  (%rdi), %rbx, %rbp
   mulxq  0x8(%rdi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rdi), %rax, %rcx
   adcq %rax, %r12
   mulxq  0x18(%rdi), %rax, %rdx
   adcq %rax, %rcx
   adcq $0x0, %rdx
   addq %rbx, %r9
   adcq %rbp, %r10
   adcq %r12, %r13
   adcq %r11, %rcx
   adcq %rdx, %r8
   vmovq  %xmm1, %r11
   movq 0x10(%r11), %r11
   movq %r11, %rdx
   mulxq  (%rsi), %rbx, %rbp
   mulxq  0x8(%rsi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rsi), %rax, %r11
   adcq %rax, %r12
   mulxq  0x18(%rsi), %rax, %rdx
   adcq %rax, %r11
   adcq $0x0, %rdx
   addq %rbx, %r10
   adcq %rbp, %r13
   adcq %r12, %rcx
   adcq %r8, %r11
   adcq %rdx, %r9
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %r10
   movq %rax, %r8
   movq %r8, %rdx
   mulxq  (%rdi), %rbx, %rbp
   mulxq  0x8(%rdi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rdi), %rax, %r8
   adcq %rax, %r12
   mulxq  0x18(%rdi), %rax, %rdx
   adcq %rax, %r8
   adcq $0x0, %rdx
   addq %rbx, %r10
   adcq %rbp, %r13
   adcq %r12, %rcx
   adcq %r11, %r8
   adcq %rdx, %r9
   vmovq  %xmm1, %r11
   movq 0x18(%r11), %r11
   movq %r11, %rdx
   mulxq  (%rsi), %rbx, %rbp
   mulxq  0x8(%rsi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rsi), %rax, %r11
   adcq %rax, %r12
   mulxq  0x18(%rsi), %rax, %rdx
   adcq %rax, %r11
   adcq $0x0, %rdx
   addq %rbx, %r13
   adcq %rbp, %rcx
   adcq %r12, %r8
   adcq %r9, %r11
   adcq %rdx, %r10
   movabsq  $-0x782df87d1b799c77, %rax # imm = 0x87D20782E4866389
   mulq %r13
   movq %rax, %r9
   movq %r9, %rdx
   mulxq  (%rdi), %rbx, %rbp
   mulxq  0x8(%rdi), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%rdi), %rax, %r9
   adcq %rax, %r12
   mulxq  0x18(%rdi), %rax, %rdx
   adcq %rax, %r9
   adcq $0x0, %rdx
   addq %rbx, %r13
   adcq %rbp, %rcx
   adcq %r12, %r8
   adcq %r11, %r9
   adcq %rdx, %r10
   movq %rcx, %rbx
   movq %r8, %rbp
   movq %r9, %r12
   movq %r10, %rdx
   subq (%rdi), %rcx
   sbbq 0x8(%rdi), %r8
   sbbq 0x10(%rdi), %r9
   sbbq 0x18(%rdi), %r10
   cmovbq %rbx, %rcx
   cmovbq %rbp, %r8
   cmovbq %r12, %r9
   cmovbq %rdx, %r10
   vmovq  %xmm0, %rdi
   movq %rcx, (%rdi)
   movq %r8, 0x8(%rdi)
   movq %r9, 0x10(%rdi)
   movq %r10, 0x18(%rdi)
   retq
SIZE(mclx_Fp_mul)

.global PRE(mclx_Fp2_sqr)
.balign 16

PRE(mclx_Fp2_sqr):
TYPE(mclx_Fp2_sqr)
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   subq $0x78, %rsp
   movq %rdx, %r11
   movq %rdi, (%rsp)
   movq %rsi, 0x8(%rsp)
   leaq 0x10(%rsp), %rdi
   movq 0x20(%rsi), %rcx
   movq 0x28(%rsi), %r8
   movq 0x30(%rsi), %r9
   movq 0x38(%rsi), %r10
   shldq  $0x1, %r9, %r10
   shldq  $0x1, %r8, %r9
   shldq  $0x1, %rcx, %r8
   shlq %rcx
   movq %rcx, (%rdi)
   movq %r8, 0x8(%rdi)
   movq %r9, 0x10(%rdi)
   movq %r10, 0x18(%rdi)
   movq %rdi, %rsi
   movq 0x8(%rsp), %r11
   callq mclx_Fp_mulL0
   movq 0x8(%rsp), %rdi
   movq (%rdi), %rcx
   movq 0x8(%rdi), %r8
   movq 0x10(%rdi), %r9
   movq 0x18(%rdi), %r10
   movq 0x20(%rdi), %rbx
   movq 0x28(%rdi), %rbp
   movq 0x30(%rdi), %r12
   movq 0x38(%rdi), %r13
   movq %rcx, %rax
   addq %rbx, %rax
   movq %rax, 0x30(%rsp)
   movq %r8, %rax
   adcq %rbp, %rax
   movq %rax, 0x38(%rsp)
   movq %r9, %rax
   adcq %r12, %rax
   movq %rax, 0x40(%rsp)
   movq %r10, %rax
   adcq %r13, %rax
   movq %rax, 0x48(%rsp)
   leaq PRE(BN_P)(%rip), %rax
   addq (%rax), %rcx
   adcq 0x8(%rax), %r8
   adcq 0x10(%rax), %r9
   adcq 0x18(%rax), %r10
   subq %rbx, %rcx
   sbbq %rbp, %r8
   sbbq %r12, %r9
   sbbq %r13, %r10
   movq %rcx, 0x50(%rsp)
   movq %r8, 0x58(%rsp)
   movq %r9, 0x60(%rsp)
   movq %r10, 0x68(%rsp)
   movq (%rsp), %rdi
   leaq 0x30(%rsp), %rsi
   leaq 0x50(%rsp), %r11
   callq mclx_Fp_mulL0
   movq (%rsp), %rdi
   movq 0x10(%rsp), %rax
   movq %rax, 0x20(%rdi)
   movq 0x18(%rsp), %rax
   movq %rax, 0x28(%rdi)
   movq 0x20(%rsp), %rax
   movq %rax, 0x30(%rdi)
   movq 0x28(%rsp), %rax
   movq %rax, 0x38(%rdi)
   addq $0x78, %rsp
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   retq
SIZE(mclx_Fp2_sqr)

.global PRE(mclx_Fp2dbl_mulPre)
.balign 16

PRE(mclx_Fp2dbl_mulPre):
TYPE(mclx_Fp2dbl_mulPre)
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   movq %rdx, %r11
   callq mclx_Fp2dbl_mulPreL0
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   retq
mclx_Fp2dbl_mulPreL0:
   subq $0x98, %rsp
   movq %rdi, (%rsp)
   movq %rsi, 0x8(%rsp)
   movq %r11, 0x10(%rsp)
   movq (%rsi), %rax
   addq 0x20(%rsi), %rax
   movq %rax, 0x18(%rsp)
   movq 0x8(%rsi), %rax
   adcq 0x28(%rsi), %rax
   movq %rax, 0x20(%rsp)
   movq 0x10(%rsi), %rax
   adcq 0x30(%rsi), %rax
   movq %rax, 0x28(%rsp)
   movq 0x18(%rsi), %rax
   adcq 0x38(%rsi), %rax
   movq %rax, 0x30(%rsp)
   movq (%r11), %rax
   addq 0x20(%r11), %rax
   movq %rax, 0x38(%rsp)
   movq 0x8(%r11), %rax
   adcq 0x28(%r11), %rax
   movq %rax, 0x40(%rsp)
   movq 0x10(%r11), %rax
   adcq 0x30(%r11), %rax
   movq %rax, 0x48(%rsp)
   movq 0x18(%r11), %rax
   adcq 0x38(%r11), %rax
   movq %rax, 0x50(%rsp)
   leaq 0x40(%rdi), %rdi
   movq 0x18(%rsp), %rdx
   mulxq  0x38(%rsp), %rax, %rcx
   movq %rax, (%rdi)
   mulxq  0x40(%rsp), %rax, %r8
   addq %rax, %rcx
   mulxq  0x48(%rsp), %rax, %r9
   adcq %rax, %r8
   mulxq  0x50(%rsp), %rax, %r10
   adcq %rax, %r9
   adcq $0x0, %r10
   movq 0x20(%rsp), %r15
   movq %r15, %rdx
   mulxq  0x38(%rsp), %rbp, %r12
   mulxq  0x40(%rsp), %rax, %r13
   addq %rax, %r12
   mulxq  0x48(%rsp), %rax, %r15
   adcq %rax, %r13
   mulxq  0x50(%rsp), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbp, %rcx
   adcq %r12, %r8
   adcq %r13, %r9
   adcq %r15, %r10
   adcq $0x0, %rdx
   movq %rdx, %r14
   movq %rcx, 0x8(%rdi)
   movq 0x28(%rsp), %r15
   movq %r15, %rdx
   mulxq  0x38(%rsp), %rbx, %rbp
   mulxq  0x40(%rsp), %rax, %r12
   addq %rax, %rbp
   mulxq  0x48(%rsp), %rax, %r15
   adcq %rax, %r12
   mulxq  0x50(%rsp), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %r15, %r14
   adcq $0x0, %rdx
   movq %rdx, %r13
   movq %r8, 0x10(%rdi)
   movq 0x30(%rsp), %r15
   movq %r15, %rdx
   mulxq  0x38(%rsp), %r8, %rbx
   mulxq  0x40(%rsp), %rax, %rbp
   addq %rax, %rbx
   mulxq  0x48(%rsp), %rax, %r15
   adcq %rax, %rbp
   mulxq  0x50(%rsp), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %r8, %r9
   adcq %rbx, %r10
   adcq %rbp, %r14
   adcq %r15, %r13
   adcq $0x0, %rdx
   movq %r9, 0x18(%rdi)
   movq %r10, 0x20(%rdi)
   movq %r14, 0x28(%rdi)
   movq %r13, 0x30(%rdi)
   movq %rdx, 0x38(%rdi)
   movq (%rsp), %rdi
   movq 0x8(%rsp), %rsi
   movq 0x10(%rsp), %r11
   movq (%rsi), %rdx
   mulxq  (%r11), %rax, %rcx
   movq %rax, (%rdi)
   mulxq  0x8(%r11), %rax, %r8
   addq %rax, %rcx
   mulxq  0x10(%r11), %rax, %r9
   adcq %rax, %r8
   mulxq  0x18(%r11), %rax, %r10
   adcq %rax, %r9
   adcq $0x0, %r10
   movq 0x8(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %rbp, %r12
   mulxq  0x8(%r11), %rax, %r13
   addq %rax, %r12
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %r13
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbp, %rcx
   adcq %r12, %r8
   adcq %r13, %r9
   adcq %r15, %r10
   adcq $0x0, %rdx
   movq %rdx, %r14
   movq %rcx, 0x8(%rdi)
   movq 0x10(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %rbx, %rbp
   mulxq  0x8(%r11), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %r12
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %r15, %r14
   adcq $0x0, %rdx
   movq %rdx, %r13
   movq %r8, 0x10(%rdi)
   movq 0x18(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %r8, %rbx
   mulxq  0x8(%r11), %rax, %rbp
   addq %rax, %rbx
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %rbp
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %r8, %r9
   adcq %rbx, %r10
   adcq %rbp, %r14
   adcq %r15, %r13
   adcq $0x0, %rdx
   movq %r9, 0x18(%rdi)
   movq %r10, 0x20(%rdi)
   movq %r14, 0x28(%rdi)
   movq %r13, 0x30(%rdi)
   movq %rdx, 0x38(%rdi)
   movq 0x8(%rsp), %rsi
   addq $0x20, %rsi
   movq 0x10(%rsp), %r11
   addq $0x20, %r11
   movq (%rsi), %rdx
   mulxq  (%r11), %rax, %rcx
   movq %rax, 0x58(%rsp)
   mulxq  0x8(%r11), %rax, %r8
   addq %rax, %rcx
   mulxq  0x10(%r11), %rax, %r9
   adcq %rax, %r8
   mulxq  0x18(%r11), %rax, %r10
   adcq %rax, %r9
   adcq $0x0, %r10
   movq 0x8(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %rbp, %r12
   mulxq  0x8(%r11), %rax, %r13
   addq %rax, %r12
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %r13
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbp, %rcx
   adcq %r12, %r8
   adcq %r13, %r9
   adcq %r15, %r10
   adcq $0x0, %rdx
   movq %rdx, %r14
   movq %rcx, 0x60(%rsp)
   movq 0x10(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %rbx, %rbp
   mulxq  0x8(%r11), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %r12
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %r15, %r14
   adcq $0x0, %rdx
   movq %rdx, %r13
   movq %r8, 0x68(%rsp)
   movq 0x18(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %r8, %rbx
   mulxq  0x8(%r11), %rax, %rbp
   addq %rax, %rbx
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %rbp
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %r8, %r9
   adcq %rbx, %r10
   adcq %rbp, %r14
   adcq %r15, %r13
   adcq $0x0, %rdx
   movq %r9, 0x70(%rsp)
   movq %r10, 0x78(%rsp)
   movq %r14, 0x80(%rsp)
   movq %r13, 0x88(%rsp)
   movq %rdx, 0x90(%rsp)
   movq (%rsp), %rdi
   movq 0x40(%rdi), %rcx
   movq 0x48(%rdi), %r8
   movq 0x50(%rdi), %r9
   movq 0x58(%rdi), %r10
   movq 0x60(%rdi), %rbx
   movq 0x68(%rdi), %rbp
   movq 0x70(%rdi), %r12
   movq 0x78(%rdi), %r13
   subq (%rdi), %rcx
   sbbq 0x8(%rdi), %r8
   sbbq 0x10(%rdi), %r9
   sbbq 0x18(%rdi), %r10
   sbbq 0x20(%rdi), %rbx
   sbbq 0x28(%rdi), %rbp
   sbbq 0x30(%rdi), %r12
   sbbq 0x38(%rdi), %r13
   subq 0x58(%rsp), %rcx
   sbbq 0x60(%rsp), %r8
   sbbq 0x68(%rsp), %r9
   sbbq 0x70(%rsp), %r10
   sbbq 0x78(%rsp), %rbx
   sbbq 0x80(%rsp), %rbp
   sbbq 0x88(%rsp), %r12
   sbbq 0x90(%rsp), %r13
   movq %rcx, 0x40(%rdi)
   movq %r8, 0x48(%rdi)
   movq %r9, 0x50(%rdi)
   movq %r10, 0x58(%rdi)
   movq %rbx, 0x60(%rdi)
   movq %rbp, 0x68(%rdi)
   movq %r12, 0x70(%rdi)
   movq %r13, 0x78(%rdi)
   movq (%rdi), %rax
   subq 0x58(%rsp), %rax
   movq %rax, (%rdi)
   movq 0x8(%rdi), %rax
   sbbq 0x60(%rsp), %rax
   movq %rax, 0x8(%rdi)
   movq 0x10(%rdi), %rax
   sbbq 0x68(%rsp), %rax
   movq %rax, 0x10(%rdi)
   movq 0x18(%rdi), %rax
   sbbq 0x70(%rsp), %rax
   movq %rax, 0x18(%rdi)
   movq 0x20(%rdi), %rcx
   movq 0x28(%rdi), %r8
   movq 0x30(%rdi), %r9
   movq 0x38(%rdi), %r10
   sbbq 0x78(%rsp), %rcx
   sbbq 0x80(%rsp), %r8
   sbbq 0x88(%rsp), %r9
   sbbq 0x90(%rsp), %r10
   leaq PRE(BN_ZERO)(%rip), %rax
   leaq PRE(BN_P)(%rip), %rbx
   cmovbq %rbx, %rax
   addq (%rax), %rcx
   adcq 0x8(%rax), %r8
   adcq 0x10(%rax), %r9
   adcq 0x18(%rax), %r10
   movq %rcx, 0x20(%rdi)
   movq %r8, 0x28(%rdi)
   movq %r9, 0x30(%rdi)
   movq %r10, 0x38(%rdi)
   addq $0x98, %rsp
   retq
   nop
   nopl (%rax,%rax)
SIZE(mclx_Fp2dbl_mulPre)

.global PRE(mclx_Fpdbl_mod)
.balign 16

PRE(mclx_Fpdbl_mod):
TYPE(mclx_Fpdbl_mod)
  pushq %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   movq %rdx, %r11
   callq mclx_Fpdbl_modL0
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   retq
mclx_Fpdbl_modL0:
   leaq PRE(BN_P)(%rip), %r13
   xorq %rbp, %rbp
   movq (%rsi), %rcx
   movq 0x8(%rsi), %r8
   movq 0x10(%rsi), %r9
   movq 0x18(%rsi), %r10
   movabsq  $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq  %rcx, %rdx
   xorq %rax, %rax
   mulxq  (%r13), %rax, %r12
   adoxq  %rax, %rcx
   movq 0x20(%rsi), %rbx
   adcxq  %r12, %r8
   mulxq  0x8(%r13), %rax, %r12
   adoxq  %rax, %r8
   adcxq  %r12, %r9
   mulxq  0x10(%r13), %rax, %r12
   adoxq  %rax, %r9
   adcxq  %r12, %r10
   mulxq  0x18(%r13), %rax, %r12
   adoxq  %rax, %r10
   adoxq  %rcx, %r12
   adcxq  %r12, %rbx
   setb %bpl
   movabsq  $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq  %r8, %rdx
   xorq %rax, %rax
   mulxq  (%r13), %rax, %r12
   adoxq  %rax, %r8
   movq 0x28(%rsi), %rcx
   adcxq  %r12, %r9
   mulxq  0x8(%r13), %rax, %r12
   adoxq  %rax, %r9
   adcxq  %r12, %r10
   mulxq  0x10(%r13), %rax, %r12
   adoxq  %rax, %r10
   adcxq  %r12, %rbx
   mulxq  0x18(%r13), %rax, %r12
   adoxq  %rax, %rbx
   adoxq  %r8, %r12
   adoxq  %rbp, %r12
   adcxq  %r12, %rcx
   setb %bpl
   movabsq  $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq  %r9, %rdx
   xorq %rax, %rax
   mulxq  (%r13), %rax, %r12
   adoxq  %rax, %r9
   movq 0x30(%rsi), %r8
   adcxq  %r12, %r10
   mulxq  0x8(%r13), %rax, %r12
   adoxq  %rax, %r10
   adcxq  %r12, %rbx
   mulxq  0x10(%r13), %rax, %r12
   adoxq  %rax, %rbx
   adcxq  %r12, %rcx
   mulxq  0x18(%r13), %rax, %r12
   adoxq  %rax, %rcx
   adoxq  %r9, %r12
   adoxq  %rbp, %r12
   adcxq  %r12, %r8
   setb %bpl
   movabsq  $-0x782df87d1b799c77, %rdx # imm = 0x87D20782E4866389
   imulq  %r10, %rdx
   xorq %rax, %rax
   mulxq  (%r13), %rax, %r12
   adoxq  %rax, %r10
   movq 0x38(%rsi), %r9
   adcxq  %r12, %rbx
   mulxq  0x8(%r13), %rax, %r12
   adoxq  %rax, %rbx
   adcxq  %r12, %rcx
   mulxq  0x10(%r13), %rax, %r12
   adoxq  %rax, %rcx
   adcxq  %r12, %r8
   mulxq  0x18(%r13), %rax, %r12
   adoxq  %rax, %r8
   adoxq  %r10, %r12
   adoxq  %rbp, %r12
   adcxq  %r12, %r9
   movq %rbx, %r10
   movq %rcx, %rbp
   movq %r8, %r12
   movq %r9, %rdx
   subq (%r13), %rbx
   sbbq 0x8(%r13), %rcx
   sbbq 0x10(%r13), %r8
   sbbq 0x18(%r13), %r9
   cmovbq %r10, %rbx
   cmovbq %rbp, %rcx
   cmovbq %r12, %r8
   cmovbq %rdx, %r9
   movq %rbx, (%rdi)
   movq %rcx, 0x8(%rdi)
   movq %r8, 0x10(%rdi)
   movq %r9, 0x18(%rdi)
   retq
   nop
   nopl (%rax)
SIZE(mclx_Fpdbl_mod)

.global PRE(mclx_Fp2_mul)
.balign 16

PRE(mclx_Fp2_mul):
TYPE(mclx_Fp2_mul)
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   subq $0x88, %rsp
   movq %rdx, %r11
   movq %rdi, (%rsp)
   leaq 0x8(%rsp), %rdi
   callq mclx_Fp2dbl_mulPreL0
   movq (%rsp), %rdi
   leaq 0x8(%rsp), %rsi
   callq mclx_Fpdbl_modL0
   movq (%rsp), %rdi
   addq $0x20, %rdi
   leaq 0x48(%rsp), %rsi
   callq mclx_Fpdbl_modL0
   addq $0x88, %rsp
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   retq
SIZE(mclx_Fp2_mul)

mclx_Fpdbl_mulPreL0:
   movq (%rsi), %rdx
   mulxq  (%r11), %rax, %rcx
   movq %rax, (%rdi)
   mulxq  0x8(%r11), %rax, %r8
   addq %rax, %rcx
   mulxq  0x10(%r11), %rax, %r9
   adcq %rax, %r8
   mulxq  0x18(%r11), %rax, %r10
   adcq %rax, %r9
   adcq $0x0, %r10
   movq 0x8(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %rbp, %r12
   mulxq  0x8(%r11), %rax, %r13
   addq %rax, %r12
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %r13
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbp, %rcx
   adcq %r12, %r8
   adcq %r13, %r9
   adcq %r15, %r10
   adcq $0x0, %rdx
   movq %rdx, %r14
   movq %rcx, 0x8(%rdi)
   movq 0x10(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %rbx, %rbp
   mulxq  0x8(%r11), %rax, %r12
   addq %rax, %rbp
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %r12
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %rbx, %r8
   adcq %rbp, %r9
   adcq %r12, %r10
   adcq %r15, %r14
   adcq $0x0, %rdx
   movq %rdx, %r13
   movq %r8, 0x10(%rdi)
   movq 0x18(%rsi), %r15
   movq %r15, %rdx
   mulxq  (%r11), %r8, %rbx
   mulxq  0x8(%r11), %rax, %rbp
   addq %rax, %rbx
   mulxq  0x10(%r11), %rax, %r15
   adcq %rax, %rbp
   mulxq  0x18(%r11), %rax, %rdx
   adcq %rax, %r15
   adcq $0x0, %rdx
   addq %r8, %r9
   adcq %rbx, %r10
   adcq %rbp, %r14
   adcq %r15, %r13
   adcq $0x0, %rdx
   movq %r9, 0x18(%rdi)
   movq %r10, 0x20(%rdi)
   movq %r14, 0x28(%rdi)
   movq %r13, 0x30(%rdi)
   movq %rdx, 0x38(%rdi)
   retq
   nop
   nop
   nopw %cs:(%rax,%rax)

.global PRE(mclx_Fp2dbl_sqrPre)
.balign 16

PRE(mclx_Fp2dbl_sqrPre):
TYPE(mclx_Fp2dbl_sqrPre)
   pushq  %rbx
   pushq  %rbp
   pushq  %r12
   pushq  %r13
   pushq  %r14
   pushq  %r15
   subq $0x58, %rsp
   movq %rdx, %r11
   movq %rdi, (%rsp)
   movq %rsi, 0x8(%rsp)
   movq 0x20(%rsi), %rbx
   movq 0x28(%rsi), %rbp
   movq 0x30(%rsi), %r12
   movq 0x38(%rsi), %r13
   movq %rbx, %rax
   addq %rax, %rax
   movq %rax, 0x10(%rsp)
   movq %rbp, %rax
   adcq %rax, %rax
   movq %rax, 0x18(%rsp)
   movq %r12, %rax
   adcq %rax, %rax
   movq %rax, 0x20(%rsp)
   movq %r13, %rax
   adcq %rax, %rax
   movq %rax, 0x28(%rsp)
   movq (%rsi), %rcx
   movq 0x8(%rsi), %r8
   movq 0x10(%rsi), %r9
   movq 0x18(%rsi), %r10
   addq %rbx, %rcx
   adcq %rbp, %r8
   adcq %r12, %r9
   adcq %r13, %r10
   movq %rcx, 0x30(%rsp)
   movq %r8, 0x38(%rsp)
   movq %r9, 0x40(%rsp)
   movq %r10, 0x48(%rsp)
   movq (%rsp), %rdi
   addq $0x40, %rdi
   leaq 0x10(%rsp), %rsi
   movq 0x8(%rsp), %r11
   callq mclx_Fpdbl_mulPreL0
   movq 0x8(%rsp), %rdi
   movq (%rdi), %rcx
   movq 0x8(%rdi), %r8
   movq 0x10(%rdi), %r9
   movq 0x18(%rdi), %r10
   subq 0x20(%rdi), %rcx
   sbbq 0x28(%rdi), %r8
   sbbq 0x30(%rdi), %r9
   sbbq 0x38(%rdi), %r10
   leaq PRE(BN_ZERO)(%rip), %rax
   leaq PRE(BN_P)(%rip), %rbx
   cmovbq %rbx, %rax
   addq (%rax), %rcx
   adcq 0x8(%rax), %r8
   adcq 0x10(%rax), %r9
   adcq 0x18(%rax), %r10
   movq %rcx, 0x10(%rsp)
   movq %r8, 0x18(%rsp)
   movq %r9, 0x20(%rsp)
   movq %r10, 0x28(%rsp)
   movq (%rsp), %rdi
   leaq 0x10(%rsp), %rsi
   leaq 0x30(%rsp), %r11
   callq mclx_Fpdbl_mulPreL0
   addq $0x58, %rsp
   popq %r15
   popq %r14
   popq %r13
   popq %r12
   popq %rbp
   popq %rbx
   retq
   nop
   nopl (%rax,%rax)
SIZE(mclx_Fp2dbl_sqrPre)

.global PRE(mclx_Fpdbl_sqrPre)
.balign 16

PRE(mclx_Fpdbl_sqrPre):
TYPE(mclx_Fpdbl_sqrPre)
   pushq %rbx
   pushq %rbp
   pushq %r12
   pushq %r13
   pushq %r14
   pushq %r15
   movq  %rdx, %r11
   movq  (%rsi), %r12
   movq  0x8(%rsi), %r13
   movq  0x10(%rsi), %r14
   movq  0x18(%rsi), %r15
   movq  %r12, %rdx
   mulxq %r15, %r9, %r10
   mulxq %r14, %r8, %rax
   addq  %rax, %r9
   movq  %r13, %rdx
   mulxq %r15, %rax, %rbx
   adcq  %rax, %r10
   adcq  $0x0, %rbx
   mulxq %r12, %rcx, %rax
   addq  %rax, %r8
   mulxq %r14, %rax, %rdx
   adcq  %rax, %r9
   adcq  %rdx, %r10
   movq  %r15, %rdx
   mulxq %r14, %rax, %rbp
   adcq  %rax, %rbx
   adcq  $0x0, %rbp
   movq  %rbp, %r11
   shrq  $0x3f, %r11
   shldq $0x1, %rbx, %rbp
   shldq $0x1, %r10, %rbx
   shldq $0x1, %r9, %r10
   shldq $0x1, %r8, %r9
   shldq $0x1, %rcx, %r8
   shlq  %rcx
   movq  %r12, %rdx
   mulxq %rdx, %rax, %rdx
   movq  %rax, (%rdi)
   addq  %rcx, %rdx
   movq  %rdx, 0x8(%rdi)
   movq  %r13, %rdx
   mulxq %rdx, %rax, %rdx
   adcq  %r8, %rax
   movq  %rax, 0x10(%rdi)
   adcq  %r9, %rdx
   movq  %rdx, 0x18(%rdi)
   movq  %r14, %rdx
   mulxq %rdx, %rax, %rdx
   adcq  %r10, %rax
   movq  %rax, 0x20(%rdi)
   adcq  %rbx, %rdx
   movq  %rdx, 0x28(%rdi)
   movq  %r15, %rdx
   mulxq %rdx, %rax, %rdx
   adcq  %rbp, %rax
   movq  %rax, 0x30(%rdi)
   adcq  %r11, %rdx
   movq  %rdx, 0x38(%rdi)
   popq  %r15
   popq  %r14
   popq  %r13
   popq  %r12
   popq  %rbp
   popq  %rbx
   retq
   nop
SIZE(mclx_Fpdbl_sqrPre)
