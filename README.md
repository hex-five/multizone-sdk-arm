# multizone-sdk-arm
MultiZone® Security for Arm® Cortex®-M Processors

**MultiZone® Security** is the quick and safe way to add security and separation to your Arm Cortex-M processors. MultiZone software can retrofit existing designs. If you don’t have TrustZone, or if you require finer granularity than one secure world, you can take advantage of high security separation without the need for hardware and software redesign, eliminating the complexity associated with managing a hybrid hardware/software security scheme. Cortex-M legacy designs lack the physical resources to provide the necessary separation, thus leading to larger attack surface and increased likelihood of vulnerability. To shield critical functionality from untrusted third-party components, MultiZone provides hardware-enforced, software-defined separation of multiple equally secure worlds. Unlike traditional solutions, MultiZone is self-contained, presents an extremely small attack surface, and it is policy driven, meaning that no coding is required – or in fact even allowed.

MultiZone works with any Cortex-M0+, Cortex‑M3, Cortex‑M4, and Cortex‑M7 processors.

This version of the GNU-based SDK supports the following development boards:

- [GigaDevice GD32307C-EVAL evaluation kit (GD32F207 Cortex-M4 @120MHz)](https://www.gigadevice.com/products/microcontrollers/gd32-development-tools/gd32-evaluation-boards/)
- [Microchip SMART SAM E70 Xplained evaluation kit (ATSAME70Q21 Cortex-M7 @300MHz)](http://www.microchip.com/developmenttools/productdetails/atsame70-xpld)
- [NXP MIMXRT1020-EVK (i.MX RT1020 Cortex-M7 @500MHz)](https://www.nxp.com/design/development-boards/i.mx-evaluation-and-development-boards/i.mx-rt1020-evaluation-kit:MIMXRT1020-EVK) 
- [Renesas EK-RA6M3 (R7FA6M3AH3CFC Cortex-M4 @120MHz)](https://www.renesas.com/us/en/products/software-tools/boards-and-kits/eval-kits/ek-ra6m3.html)
- [ST NUCLEO-F767ZI (STM32F767ZI Cortex-M7 @216MHz)](https://www.st.com/en/evaluation-tools/nucleo-f767zi.html)


### SDK Installation ###

The MultiZone SDK works with any versions of Linux, Windows, and Mac capable of running Java 1.8 or greater. The directions in this readme are specific to a fresh installation of Ubuntu 18.04.4 LTS. Other Linux distros are similar.

**Linux prerequisites**

```
sudo apt update
sudo apt install make default-jre gtkterm
```
Note: GtkTerm is optional and required only to connect to the reference application via UART. It is not required to build, debug, and load the MultiZone software. Any other serial terminal application of choice would do.

**GNU Arm Embedded Toolchain**

Hex Five reference version: 8-2019-q3-update Linux 64-bit July 10, 2019
```
cd ~
wget http://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2019q3/RC1.1/gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2
tar -xvf gcc-arm-none-eabi-8-2019-q3-update-linux.tar.bz2
```

**OpenOCD on-chip debugger**

Hex Five reference build: GNU MCU Eclipse 0.10.0
```
cd ~
wget http://hex-five.com/wp-content/uploads/2020/02/gnu-mcu-openocd-20190827.tar.xz
tar -xvf gnu-mcu-openocd-20190827.tar.xz
```

**Linux USB udev rules**

```
sudo vi /etc/udev/rules.d/99-openocd.rules

# STMicroelectronics ST-LINK/V2.1
SUBSYSTEM=="tty", ATTRS{idVendor}=="0483",ATTRS{idProduct}=="374b", MODE="664", GROUP="plugdev"
SUBSYSTEM=="usb", ATTRS{idVendor}=="0483",ATTRS{idProduct}=="374b", MODE="664", GROUP="plugdev"

# Atmel Corp. Xplained Pro board debugger and programmer
SUBSYSTEM=="tty", ATTRS{idVendor}=="03eb",ATTRS{idProduct}=="2111", MODE="664", GROUP="plugdev"
SUBSYSTEM=="usb", ATTRS{idVendor}=="03eb",ATTRS{idProduct}=="2111", MODE="664", GROUP="plugdev"

# NXP MIMXRT1020-EVK
SUBSYSTEM=="tty", ATTRS{idVendor}=="0d28",ATTRS{idProduct}=="0204", MODE="664", GROUP="plugdev"
SUBSYSTEM=="usb", ATTRS{idVendor}=="0d28",ATTRS{idProduct}=="0204", MODE="664", GROUP="plugdev"

# CMSIS-DAP compatible adapters
ATTRS{product}=="*CMSIS-DAP*", MODE="664", GROUP="plugdev"
```
Reboot for these changes to take effect.

**MultiZone Security SDK**

```
cd ~
wget https://github.com/hex-five/multizone-sdk-arm/archive/master.zip
unzip master.zip
```

### Build & load the MultiZone reference application ###

Connect the target board to the development machine as indicated in its user manual.

'ls bsp' shows the list of supported targets: ATSAME70  EKRA6M3  GD32307 IMXRT1020  STM32F767.

Assign one of these values to the BOARD variable - default is STM32F767.

```
cd ~/multizone-sdk-arm
export GNU_ARM=~/gcc-arm-none-eabi-8-2019-q3-update/bin
export OPENOCD=~/gnu-mcu-openocd-20190827
export BOARD=ATSAME70
make 
make load
```


### Run the MultiZone reference application ###

Connect the board UART port as indicated in its user manual.

Start the serial terminal console (GtkTerm) and connect to /dev/ttyACM0 at 115200-8-N-1

Hit the enter key a few times until the cursor 'Z1 >' appears on the screen

Enter 'restart' to display the splash screen

Hit enter again to show the list of available commands

```
=====================================================================
      	             Hex Five MultiZone® Security                    
    Copyright© 2020 Hex Five Security, Inc. - All Rights Reserved    
=====================================================================
This version of MultiZone® Security is meant for evaluation purposes 
only. As such, use of this software is governed by the Evaluation    
License. There may be other functional limitations as described in   
the evaluation SDK documentation. The commercial version of the      
software does not have these restrictions.                           
=====================================================================
Implementer    : 0x41, Arm.
Variant        : 0x1, Revision 1.
PartNo         : 0xC27, Cortex-M7.
Revision       : 0x1, Patch 1.

Z1 > 
Commands: yield send recv mpu load store exec stats timer restart

Z1>
```

### Optional: Eclipse CDT Project ###
This repository includes an optional Eclipse CDT project for developers familiar with this IDE. No additional plugins are required to build and upload MultiZone to the target. The [OpenOCD debugging plug-in](https://eclipse-embed-cdt.github.io/debug/openocd) is optional and recommended.

**Eclipse project Setup**

File > Open Projects from File System > Import source: ~/multizone-sdk-arm

Project > Properties > C/C++ Build > Environment: set GNU_ARM and OPENOCD variables according to your installation

![alt text](https://hex-five.com/wp-content/uploads/multizone-eclipse-proj.png)


### Technical Specs ###
| |
|---|
| Up to 8 separated equally secure worlds – hardware-enforced, software-defined |
| Up to 16 memory-mapped resources per zone – i.e. flash, ram, rom, i/o, etc. |
| Scheduler: preemptive, cooperative, round robin, configurable tick |
| Secure interzone communications based on messages – no shared memory |
| Built-in trap & emulation for privileged instructions – SVC, MRS, MSR, CPS, WFE, WFI |
| Support for secure user-mode interrupt handlers mapped to zones – up to 128 sources |
| Support for Wait For Interrupt and CPU suspend mode for low power applications |
| Formally verifiable runtime ~2KB, 100% written in assembly, no 3rd-party dependencies |
| C library wrapper for protected mode execution – optional for high speed / low-latency |
| Hardware requirements: Arm Cortex-M0+/M3/M4/M7 processor w/ Memory Protection Unit | 
| System requirements: 4KB for program, 2KB for data - CPU overhead < 0.01% | 
| Development environment: any versions of Linux, Windows, Mac running Java 1.8 |


### Additional Resources ###

- [MultiZone Reference Manual](http://github.com/hex-five/multizone-sdk-arm/blob/master/manual.pdf)
- [MultiZone Datasheet](http://hex-five.com/wp-content/uploads/2020/02/multizone-cortexm-datasheet-20200218.pdf)
- [Frequently Asked Questions](http://hex-five.com/faq/)
- Contact Hex Five http://hex-five.com/contact


### Legalities ###

Please remember that export/import and/or use of strong cryptography software, providing cryptography hooks, or even just communicating technical details about cryptography software is illegal in some parts of the world. So when you import this software to your country, re-distribute it from there or even just email technical suggestions or even source patches to the authors or other people you are strongly advised to pay close attention to any laws or regulations which apply to you. Hex Five Security, Inc. and the authors of the software included in this repository are not liable for any violations you make here. So be careful, it is your responsibility.


_Arm, Cortex, and TrustZone are registered trademarks of Arm Limited._

_MultiZone is a registered trademark of Hex Five Security, Inc._

_MultiZone technology is protected by patents US 11,151,262 and PCT/US2019/038774_
