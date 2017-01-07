# W90P710
用于W90P710的基于GNU ARM Eclipse的代码，包含常用的驱动库，包含STEMWIN，代码中包含一个简单的计算器和一个简单的音乐播放器
需要以下插件的支持：
CDT
GNU ARM Eclipse（用于Makefile的自动生成）
Zylin（用于下载，调试程序）
使用的GDB脚本如下：
```Python
# connect to the J-Link gdb server
target remote localhost:2331
# Set JTAG speed to 30 kHz
monitor endian little
monitor speed 30
# Reset the target
monitor reset
monitor sleep 10
# connect to the J-Link gdb server
target remote localhost:2331
# Set JTAG speed to 30 kHz
monitor endian little
monitor speed 30
# Reset the target
monitor reset
monitor sleep 10
# connect to the J-Link gdb server
target remote localhost:2331
# Set JTAG speed to 30 kHz
monitor endian little
monitor speed 30
# Reset the target
monitor reset
monitor sleep 10
monitor MemU32 0xFFF01F00  =  0xFFF01F00
monitor MemU32 0xFFF01000  =  0x000530C0
monitor MemU32 0xFFF01004  =  0xFE040080
monitor MemU32 0xFFF01008  =  0x000090E4
monitor MemU32 0xFFF01008  =  0x000090E4
monitor MemU32 0xFFF01010  =  0x0000014B
monitor MemU32 0xFFF01018  =  0xF0078001
monitor MemU32 0xFFF01004  =  0xFFF01004
```

其他资料包括原理图等在光盘里