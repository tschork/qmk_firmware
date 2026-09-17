# Mysterium ATmega32A recovery image

This directory contains a full Flash dump from a known-good Mysterium
ATmega32A. The image includes both the QMK firmware and the USBaspLoader
bootloader.

The original EEPROM, fuse and lock-bit values are also provided for reference.

## Restore the Flash image

Using a USBasp programmer, write the Flash image and restore the required
fuse values with:

```shell
avrdude -c usbasp -p m32 -v \
  -U flash:w:mysterium-good.hex:i \
  -U lfuse:w:0x1f:m \
  -U hfuse:w:0xc0:m
```
This procedure has been tested using a USBasp programmer with multiple
ATmega32A microcontrollers.

After programming, install the ATmega32A in the Mysterium. Holding BOOT
while briefly pressing RESET should start USBaspLoader and allow the
keyboard to be flashed normally through USB.

# Create a new backup

To dump the Flash, EEPROM, fuses and lock bits from a known-good ATmega32A:
```shell
avrdude -c usbasp -p m32 \
  -U flash:r:mysterium-good.hex:i \
  -U eeprom:r:mysterium-good-eeprom.hex:i \
  -U lfuse:r:mysterium-good-lfuse.txt:h \
  -U hfuse:r:mysterium-good-hfuse.txt:h \
  -U lock:r:mysterium-good-lock.txt:h
```
Expected values for this Mysterium configuration:
```
Low fuse:   0x1f
High fuse:  0xc0
Lock bits:  0xff
```
Incorrect fuse values can make an AVR inaccessible through normal ISP
programming. Verify the target is an ATmega32A used in the same Mysterium
configuration before writing them with `avrdude -c usbasp -p m32 -v`.
