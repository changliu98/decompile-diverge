void OPLL_writeReg(YM2413 *chip, unsigned int a, unsigned char v)
{
  OPLLWrite(&chip->OPLL, a, v);
}