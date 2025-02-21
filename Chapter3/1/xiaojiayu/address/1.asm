section .text
global _start
_start:
  ;mov word ptr ds:[0],1
  mov ax,0x00
  mov ds,ax
  mov bx,0x60
  mov word ptr [bx+0x0c],38
  add word ptr [bx+0x0e],70

  mov si,0
  mov byte ptr [bx+0x10+si],'V'
  inc si
  mov byte ptr [bx+0x10+si],'A'
  inc si
  mov byte ptr [bx+0x10+si],'X'  
