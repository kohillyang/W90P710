# STM32F4_USB
A small STM32F4 project built by Gnu ARM Eclipse.
This Project have done these things:
1. Implement all functions that newlib need, which means that you can use functions like `printf` and `malloc`.
2. Add USB support,if you need to use USB,just add these codes in your project:
```CPP
void usb_init(void);
usb_init();
```
for more information,please have a look at `usb_capi.c`
3. This code worked good as a AGC controler, the GUI is implemented by `stemwin`. The algorithm it uses called PI is simple.


