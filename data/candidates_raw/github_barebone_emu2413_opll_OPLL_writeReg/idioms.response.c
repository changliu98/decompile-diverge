void opll_write(struct OPLL *opll, unsigned int address, unsigned int data)
{
  int i;
  int slot;
  int patch;
  int reg = address;
  if (reg < 0x40)
  {
    if (reg >= 0x19 && reg <= 0x1f ||
        reg >= 0x29 && reg <= 0x2f ||
        reg >= 0x39)
    {
      reg -= 0x10;
    }
    opll->reg[reg] = data;
    switch (reg)
    {
      case 0x00:
        opll->patch[0].AM = (data & 0x80) >> 7;
        opll->patch[0].PM = (data & 0x40) >> 6;
        opll->patch[0].EG = (data & 0x20) >> 5;
        opll->patch[0].KR = (data & 0x10) >> 4;
        opll->patch[0].ML = data & 0x0f;
        for (i = 0; i < 9; i++)
        {
          if (opll->patch_number[i] == 0)
          {
            opll_set_slot(&opll->slot[i * 2], 12);
          }
        }
        break;
      case 0x01:
        opll->patch[1].AM = (data & 0x80) >> 7;
        opll->patch[1].PM = (data & 0x40) >> 6;
        opll->patch[1].EG = (data & 0x20) >> 5;
        opll->patch[1].KR = (data & 0x10) >> 4;
        opll->patch[1].ML = data & 0x0f;
        for (i = 0; i < 9; i++)
        {
          if (opll->patch_number[i] == 0)
          {
            opll_set_slot(&opll->slot[i * 2 + 1], 12);
          }
        }
        break;
      case 0x02:
        opll->patch[0].KL = (data & 0xc0) >> 6;
        opll->patch[0].TL = data & 0x3f;
        for (i = 0; i < 9; i++)
        {
          if (opll->patch_number[i] == 0)
          {
            opll_set_slot(&opll->slot[i * 2], 2);
          }
        }
        break;
      case 0x03:
        opll->patch[1].KL = (data & 0xc0) >> 6;
        opll->patch[1].WS = (data & 0x20) >> 4;
        opll->patch[0].WS = (data & 0x10) >> 3;
        opll->patch[0].FB = data & 0x07;
        for (i = 0; i < 9; i++)
        {
          if (opll->patch_number[i] == 0)
          {
            opll_set_slot(&opll->slot[i * 2], 1);
            opll_set_slot(&opll->slot[i * 2 + 1], 3);
          }
        }
        break;
      case 0x04:
        opll->patch[0].AR = (data & 0xf0) >> 4;
        opll->patch[0].DR = data & 0x0f;
        for (i = 0; i < 9; i++)
        {
          if (opll->patch_number[i] == 0)
          {
            opll_set_slot(&opll->slot[i * 2], 8);
          }
        }
        break;
      case 0x05:
        opll->patch[1].AR = (data & 0xf0) >> 4;
        opll->patch[1].DR = data &