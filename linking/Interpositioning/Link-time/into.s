
int.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	bf 20 00 00 00       	mov    $0x20,%edi
  11:	e8 00 00 00 00       	call   16 <main+0x16>
  16:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1e:	48 89 c7             	mov    %rax,%rdi
  21:	e8 00 00 00 00       	call   26 <main+0x26>
  26:	b8 00 00 00 00       	mov    $0x0,%eax
  2b:	c9                   	leave
  2c:	c3                   	ret

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	00 47 43             	add    %al,0x43(%rdi)
   3:	43 3a 20             	rex.XB cmp (%r8),%spl
   6:	28 55 62             	sub    %dl,0x62(%rbp)
   9:	75 6e                	jne    79 <main+0x79>
   b:	74 75                	je     82 <main+0x82>
   d:	20 31                	and    %dh,(%rcx)
   f:	33 2e                	xor    (%rsi),%ebp
  11:	33 2e                	xor    (%rsi),%ebp
  13:	30 2d 36 75 62 75    	xor    %ch,0x75627536(%rip)        # 7562754f <main+0x7562754f>
  19:	6e                   	outsb  %ds:(%rsi),(%dx)
  1a:	74 75                	je     91 <main+0x91>
  1c:	32 7e 32             	xor    0x32(%rsi),%bh
  1f:	34 2e                	xor    $0x2e,%al
  21:	30 34 29             	xor    %dh,(%rcx,%rbp,1)
  24:	20 31                	and    %dh,(%rcx)
  26:	33 2e                	xor    (%rsi),%ebp
  28:	33 2e                	xor    (%rsi),%ebp
  2a:	30 00                	xor    %al,(%rax)

Disassembly of section .note.gnu.property:

0000000000000000 <.note.gnu.property>:
   0:	04 00                	add    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	10 00                	adc    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	05 00 00 00 47       	add    $0x47000000,%eax
   d:	4e 55                	rex.WRX push %rbp
   f:	00 02                	add    %al,(%rdx)
  11:	00 00                	add    %al,(%rax)
  13:	c0 04 00 00          	rolb   $0x0,(%rax,%rax,1)
  17:	00 03                	add    %al,(%rbx)
  19:	00 00                	add    %al,(%rax)
  1b:	00 00                	add    %al,(%rax)
  1d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .eh_frame:

0000000000000000 <.eh_frame>:
   0:	14 00                	adc    $0x0,%al
   2:	00 00                	add    %al,(%rax)
   4:	00 00                	add    %al,(%rax)
   6:	00 00                	add    %al,(%rax)
   8:	01 7a 52             	add    %edi,0x52(%rdx)
   b:	00 01                	add    %al,(%rcx)
   d:	78 10                	js     1f <.eh_frame+0x1f>
   f:	01 1b                	add    %ebx,(%rbx)
  11:	0c 07                	or     $0x7,%al
  13:	08 90 01 00 00 1c    	or     %dl,0x1c000001(%rax)
  19:	00 00                	add    %al,(%rax)
  1b:	00 1c 00             	add    %bl,(%rax,%rax,1)
  1e:	00 00                	add    %al,(%rax)
  20:	00 00                	add    %al,(%rax)
  22:	00 00                	add    %al,(%rax)
  24:	2d 00 00 00 00       	sub    $0x0,%eax
  29:	45 0e                	rex.RB (bad)
  2b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  31:	64 0c 07             	fs or  $0x7,%al
  34:	08 00                	or     %al,(%rax)
	...
