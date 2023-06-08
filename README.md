# SDI

Q1: Is size of SAV, EAV fixed?
  Sure. 0x3ff 0x000 0x000 0xXYZ. So it is 4 * 16bits = 64bits.

Q2: Bit depth?
  10 bits color, but we use 16bits.

Q3: Is Y Cb Cr interleaved?
  Yes. We have to pack this into following format, then sent it to FPGA.

Data stream one
SAV1 Y0 Y1 Y2 Y3 EAV1
Data stream two
SAV2 U0 V0 U1 V1 EAV2

-> SDI Raw:

One line:
0x3ff(SAV2) 0x3ff(SAV1) 0x000(SAV2) 0x000(SAV1) 0x000(SAV2) 0x000(SAV1) 0xXYZ(SAV2) 0xXYZ(SAV1) U0 Y0 V0 Y1 U1 Y2 V1 Y3 ... U959 Y1918 V959 Y1919 0x3ff(EAV2) 0x3ff(EAV1) 0x000(EAV2) 0x000(EAV1) 0x000(EAV2) 0x000(EAV1) 0xXYZ(EAV2) 0xXYZ(EAV1) Blank2 Blank1 ....(repeat)

Q4: How do we do fast multiplex?
