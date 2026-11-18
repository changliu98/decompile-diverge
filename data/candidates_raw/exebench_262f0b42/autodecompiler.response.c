void set_fcs_bits(unsigned short *fcs_bits, unsigned short fcs)
{
 int i;

 for (i = 0; i < 14; i++)
  fcs_bits[i] = 0;
 if (fcs >= 4096) { fcs_bits[12] = 1; fcs -= 4096; }
 if (fcs >= 2048) { fcs_bits[11] = 1; fcs -= 2048; }
 if (fcs >= 1024) { fcs_bits[10] = 1; fcs -= 1024; }
 if (fcs >= 512) { fcs_bits[9] = 1; fcs -= 512; }
 if (fcs >= 256) { fcs_bits[8] = 1; fcs -= 256; }
 if (fcs >= 128) { fcs_bits[7] = 1; fcs -= 128; }
 if (fcs >= 64) { fcs_bits[6] = 1; fcs -= 64; }
 if (fcs >= 32) { fcs_bits[5] = 1; fcs -= 32; }
 if (fcs >= 16) { fcs_bits[4] = 1; fcs -= 16; }
 if (fcs >= 8) { fcs_bits[3] = 1; fcs -= 8; }
 if (fcs >= 4) { fcs_bits[2] = 1; fcs -= 4; }
 if (fcs >= 2) { fcs_bits[1] = 1; fcs -= 2; }
 if (fcs == 1) { fcs_bits[0] = 1; }
}