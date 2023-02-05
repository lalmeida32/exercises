# Boot Sector

The boot sector is the first 512 bytes of a disk device, ending in `0xaa55`.

The bios identifies these devices and load the boot sector in main memory, in
the 0x7c00 position. Then it runs the boot sector, the operating system starting
point.

To simulate that, I used nasm, qemu and virtualbox with a flat vmdk file.

- nasm converts from x86 assembly to x86 binary code
- qemu emulates a CPU which I can run my boot sector (faster than VMs)
- virtualbox emulates an entire computer, using a vmdk file as disk (which means
  the first 512 bytes of this file corresponds to the boot sector)

Thanks to Nick Blundell document: Writing a Simple Operating System — from
Scratch
