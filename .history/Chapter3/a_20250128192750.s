
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 8a 2f 00 00    	push   0x2f8a(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 8c 2f 00 00    	jmp    *0x2f8c(%rip)        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   $0x0
    1039:	e9 e2 ff ff ff       	jmp    1020 <_init+0x20>
    103e:	66 90                	xchg   %ax,%ax
    1040:	f3 0f 1e fa          	endbr64
    1044:	68 01 00 00 00       	push   $0x1
    1049:	e9 d2 ff ff ff       	jmp    1020 <_init+0x20>
    104e:	66 90                	xchg   %ax,%ax
    1050:	f3 0f 1e fa          	endbr64
    1054:	68 02 00 00 00       	push   $0x2
    1059:	e9 c2 ff ff ff       	jmp    1020 <_init+0x20>
    105e:	66 90                	xchg   %ax,%ax

Disassembly of section .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:	f3 0f 1e fa          	endbr64
    1064:	ff 25 8e 2f 00 00    	jmp    *0x2f8e(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    106a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001070 <puts@plt>:
    1070:	f3 0f 1e fa          	endbr64
    1074:	ff 25 46 2f 00 00    	jmp    *0x2f46(%rip)        # 3fc0 <puts@GLIBC_2.2.5>
    107a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001080 <__stack_chk_fail@plt>:
    1080:	f3 0f 1e fa          	endbr64
    1084:	ff 25 3e 2f 00 00    	jmp    *0x2f3e(%rip)        # 3fc8 <__stack_chk_fail@GLIBC_2.4>
    108a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000001090 <getchar@plt>:
    1090:	f3 0f 1e fa          	endbr64
    1094:	ff 25 36 2f 00 00    	jmp    *0x2f36(%rip)        # 3fd0 <getchar@GLIBC_2.2.5>
    109a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010a0 <_start>:
    10a0:	f3 0f 1e fa          	endbr64
    10a4:	31 ed                	xor    %ebp,%ebp
    10a6:	49 89 d1             	mov    %rdx,%r9
    10a9:	5e                   	pop    %rsi
    10aa:	48 89 e2             	mov    %rsp,%rdx
    10ad:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10b1:	50                   	push   %rax
    10b2:	54                   	push   %rsp
    10b3:	45 31 c0             	xor    %r8d,%r8d
    10b6:	31 c9                	xor    %ecx,%ecx
    10b8:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 1189 <main>
    10bf:	ff 15 13 2f 00 00    	call   *0x2f13(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    10c5:	f4                   	hlt
    10c6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10cd:	00 00 00 

00000000000010d0 <deregister_tm_clones>:
    10d0:	48 8d 3d 39 2f 00 00 	lea    0x2f39(%rip),%rdi        # 4010 <__TMC_END__>
    10d7:	48 8d 05 32 2f 00 00 	lea    0x2f32(%rip),%rax        # 4010 <__TMC_END__>
    10de:	48 39 f8             	cmp    %rdi,%rax
    10e1:	74 15                	je     10f8 <deregister_tm_clones+0x28>
    10e3:	48 8b 05 f6 2e 00 00 	mov    0x2ef6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10ea:	48 85 c0             	test   %rax,%rax
    10ed:	74 09                	je     10f8 <deregister_tm_clones+0x28>
    10ef:	ff e0                	jmp    *%rax
    10f1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10f8:	c3                   	ret
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <register_tm_clones>:
    1100:	48 8d 3d 09 2f 00 00 	lea    0x2f09(%rip),%rdi        # 4010 <__TMC_END__>
    1107:	48 8d 35 02 2f 00 00 	lea    0x2f02(%rip),%rsi        # 4010 <__TMC_END__>
    110e:	48 29 fe             	sub    %rdi,%rsi
    1111:	48 89 f0             	mov    %rsi,%rax
    1114:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1118:	48 c1 f8 03          	sar    $0x3,%rax
    111c:	48 01 c6             	add    %rax,%rsi
    111f:	48 d1 fe             	sar    $1,%rsi
    1122:	74 14                	je     1138 <register_tm_clones+0x38>
    1124:	48 8b 05 c5 2e 00 00 	mov    0x2ec5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    112b:	48 85 c0             	test   %rax,%rax
    112e:	74 08                	je     1138 <register_tm_clones+0x38>
    1130:	ff e0                	jmp    *%rax
    1132:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1138:	c3                   	ret
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <__do_global_dtors_aux>:
    1140:	f3 0f 1e fa          	endbr64
    1144:	80 3d c5 2e 00 00 00 	cmpb   $0x0,0x2ec5(%rip)        # 4010 <__TMC_END__>
    114b:	75 2b                	jne    1178 <__do_global_dtors_aux+0x38>
    114d:	55                   	push   %rbp
    114e:	48 83 3d a2 2e 00 00 	cmpq   $0x0,0x2ea2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1155:	00 
    1156:	48 89 e5             	mov    %rsp,%rbp
    1159:	74 0c                	je     1167 <__do_global_dtors_aux+0x27>
    115b:	48 8b 3d a6 2e 00 00 	mov    0x2ea6(%rip),%rdi        # 4008 <__dso_handle>
    1162:	e8 f9 fe ff ff       	call   1060 <__cxa_finalize@plt>
    1167:	e8 64 ff ff ff       	call   10d0 <deregister_tm_clones>
    116c:	c6 05 9d 2e 00 00 01 	movb   $0x1,0x2e9d(%rip)        # 4010 <__TMC_END__>
    1173:	5d                   	pop    %rbp
    1174:	c3                   	ret
    1175:	0f 1f 00             	nopl   (%rax)
    1178:	c3                   	ret
    1179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001180 <frame_dummy>:
    1180:	f3 0f 1e fa          	endbr64
    1184:	e9 77 ff ff ff       	jmp    1100 <register_tm_clones>

0000000000001189 <main>:
    1189:	f3 0f 1e fa          	endbr64
    118d:	55                   	push   %rbp
    118e:	48 89 e5             	mov    %rsp,%rbp
    1191:	48 83 ec 10          	sub    $0x10,%rsp
    1195:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    119c:	00 00 
    119e:	48 89 45 f8          	mov    %rax,-0x10(%rbp)
    11a2:	31 c0                	xor    %eax,%eax
    11a4:	48 8d 45 f4          	lea    -0xc(%rbp),%rax
    11a8:	48 89 c7             	mov    %rax,%rdi
    11ab:	e8 27 00 00 00       	call   11d7 <gets>
    11b0:	48 8d 45 f4          	lea    -0xc(%rbp),%rax
    11b4:	48 89 c7             	mov    %rax,%rdi
    11b7:	e8 b4 fe ff ff       	call   1070 <puts@plt>
    11bc:	b8 00 00 00 00       	mov    $0x0,%eax
    11c1:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    11c5:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    11cc:	00 00 
    11ce:	74 05                	je     11d5 <main+0x4c>
    11d0:	e8 ab fe ff ff       	call   1080 <__stack_chk_fail@plt>
    11d5:	c9                   	leave
    11d6:	c3                   	ret

00000000000011d7 <gets>:
    11d7:	f3 0f 1e fa          	endbr64
    11db:	55                   	push   %rbp
    11dc:	48 89 e5             	mov    %rsp,%rbp
    11df:	48 83 ec 20          	sub    $0x20,%rsp
    11e3:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    11e7:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    11eb:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    11ef:	e8 9c fe ff ff       	call   1090 <getchar@plt>
    11f4:	89 45 f4             	mov    %eax,-0xc(%rbp)
    11f7:	eb 18                	jmp    1211 <gets+0x3a>
    11f9:	8b 45 f4             	mov    -0xc(%rbp),%eax
    11fc:	89 c2                	mov    %eax,%edx
    11fe:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1202:	88 10                	mov    %dl,(%rax)
    1204:	e8 87 fe ff ff       	call   1090 <getchar@plt>
    1209:	89 45 f4             	mov    %eax,-0xc(%rbp)
    120c:	48 83 45 f8 01       	addq   $0x1,-0x8(%rbp)
    1211:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%rbp)
    1215:	74 06                	je     121d <gets+0x46>
    1217:	83 7d f4 0a          	cmpl   $0xa,-0xc(%rbp)
    121b:	75 dc                	jne    11f9 <gets+0x22>
    121d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1221:	c9                   	leave
    1222:	c3                   	ret

Disassembly of section .fini:

0000000000001224 <_fini>:
    1224:	f3 0f 1e fa          	endbr64
    1228:	48 83 ec 08          	sub    $0x8,%rsp
    122c:	48 83 c4 08          	add    $0x8,%rsp
    1230:	c3                   	ret
