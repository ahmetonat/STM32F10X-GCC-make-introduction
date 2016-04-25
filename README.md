# STM32F10X-GCC-make-introduction
Tutorial of how to setup an environment to program STM32F103 microcontroller from the command line with GCC

See the accompanying blog post at: http://aviatorahmet.blogspot.com/2016/04/arm-stm32f10x-programming-with-gcc.html
for complete information. It targets the STM32F103RB Nucleo board since that is widely available, but any similar board can be used instead.

The project is self contained. It will compile if:
1. GCC ARM Embedded is installed: https://launchpad.net/gcc-arm-embedded
2. make is installed and
3. Some means of burning the code on the processor is installed. (Nucleo is good because it can program itself)

To be able to compile, modify the path declaration values in the Makefile : 
  TOOLROOT=
  LIBROOT=
to match your installation.

The end result simply blinks the on board LED. But is also proves that all of the tools are installed and set up correctly and you are now free to go ahead writing new programs.
