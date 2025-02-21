section .text
global _start
_start:
  mov ax,0x0123
  mov bx,0x0456
  add ax,bx

  mov rax,60
  xor rdi,rdi
  syscall
  ;作用是退出程序,int 21h是DOS的调用,这里是Linux的调用
  ;Segmentation fault (core dumped),这里是因为没有退出程序,所以会出现这个错误