section .text
global _start

_start:
  ; 这里我没注意内存中的字长是多少
  mov rax,0xffff
  mov ds,rax
  mov rdx,ds:[0x0006]
  mov rcx,2
_mul:
  add rdx,rdx
  loop _mul

  mov rax,1
  xor edi,edi
  syscall


