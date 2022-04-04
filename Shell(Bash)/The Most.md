*这里是学习用到的所有指令的合辑*

*如果系统学习某一部分的指令，会单开一个子目录进行总结！*

*这里都是零散的指令*

# readelf

## readelf -h filename		查看ELF header具体信息

```bash
┌──(kali㉿kali)-[~/桌面]
└─$ readelf -h test                                                                 1 ⨯
ELF 头：
Magic：  7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
类别:                              ELF64
数据:                              2 补码，小端序 (little endian)
Version:                           1 (current)
OS/ABI:                            UNIX - System V
ABI 版本:                          0
类型:                              DYN (共享目标文件)
系统架构:                          Advanced Micro Devices X86-64
版本:                              0x1
入口点地址：              0x1050
程序头起点：              64 (bytes into file)
Start of section headers:          14808 (bytes into file)
标志：             0x0
Size of this header:               64 (bytes)
Size of program headers:           56 (bytes)
Number of program headers:         11
Size of section headers:           64 (bytes)
Number of section headers:         30
Section header string table index: 29
```

## readelf -l		查看program header程序头信息

```bash
┌──(kali㉿kali)-[~/桌面]
└─$ readelf -l test                                                                 1 ⨯

Elf 文件类型为 DYN (共享目标文件)
Entry point 0x1050
There are 11 program headers, starting at offset 64

程序头：
Type           Offset             VirtAddr           PhysAddr
FileSiz            MemSiz              Flags  Align
PHDR           0x0000000000000040 0x0000000000000040 0x0000000000000040
0x0000000000000268 0x0000000000000268  R      0x8
INTERP         0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
0x000000000000001c 0x000000000000001c  R      0x1
[Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000568 0x0000000000000568  R      0x1000
LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
0x00000000000001dd 0x00000000000001dd  R E    0x1000
LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
0x0000000000000170 0x0000000000000170  R      0x1000
LOAD           0x0000000000002de8 0x0000000000003de8 0x0000000000003de8
0x0000000000000248 0x0000000000000250  RW     0x1000
DYNAMIC        0x0000000000002df8 0x0000000000003df8 0x0000000000003df8
0x00000000000001e0 0x00000000000001e0  RW     0x8
NOTE           0x00000000000002c4 0x00000000000002c4 0x00000000000002c4
0x0000000000000044 0x0000000000000044  R      0x4
GNU_EH_FRAME   0x0000000000002028 0x0000000000002028 0x0000000000002028
0x000000000000003c 0x000000000000003c  R      0x4
GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
0x0000000000000000 0x0000000000000000  RW     0x10
GNU_RELRO      0x0000000000002de8 0x0000000000003de8 0x0000000000003de8
0x0000000000000218 0x0000000000000218  R      0x1

Section to Segment mapping:
段节...
00     
01     .interp 
02     .interp .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt 
03     .init .plt .plt.got .text .fini 
04     .rodata .eh_frame_hdr .eh_frame 
05     .init_array .fini_array .dynamic .got .got.plt .data .bss 
06     .dynamic 
07     .note.gnu.build-id .note.ABI-tag 
08     .eh_frame_hdr 
09     
10     .init_array .fini_array .dynamic .got 
```
