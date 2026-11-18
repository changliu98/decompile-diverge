void OPLL_writeReg(OPLL *opll, uint32_t reg, uint8_t data)
{
    int i;
    int ch;

    if (reg >= 0x40)
    {
        return;
    }

    if ((reg >= 0x19 && reg <= 0x1f) || (reg >= 0x29 && reg <= 0x2f) || (reg >= 0x39 && reg <= 0x3f))
    {
        reg -= 0x09;
    }

    opll->reg[reg] = data;

    switch (reg)
    {
    case 0x00:
        opll->patch[0].AM = data >> 7;
        opll->patch[0].PM = (data >> 6) & 0x01;
        opll->patch[0].EG = (data >> 5) & 0x01;
        opll->patch[0].KR = (data >> 4) & 0x01;
        opll->patch[0].ML = data & 0x0f;
        for (i = 0; i < 9; i++)
        {
            if (opll->patch_number[i] == 0)
            {
                request_update(&opll->slot[i * 2 + 0], 0x08 | 0x04);
            }
        }
        break;

    case 0x01:
        opll->patch[1].AM = data >> 7;
        opll->patch[1].PM = (data >> 6) & 0x01;
        opll->patch[1].EG = (data >> 5) & 0x01;
        opll->patch[1].KR = (data >> 4) & 0x01;
        opll->patch[1].ML = data & 0x0f;
        for (i = 0; i < 9; i++)
        {
            if (opll->patch_number[i] == 0)
            {
                request_update(&opll->slot[i * 2 + 1], 0x08 | 0x04);
            }
        }
        break;

    case 0x02:
        opll->patch[0].KL = data >> 6;
        opll->patch[0].TL = data & 0x3f;
        for (i = 0; i < 9; i++)
        {
            if (opll->patch_number[i] == 0)
            {
                request_update(&opll->slot[i * 2 + 0], 0x02);
            }
        }
        break;

    case 0x03:
        opll->patch[1].KL = data >> 6;
        opll->patch[1].WS = (data >> 4) & 0x01;
        opll->patch[0].WS = (data >> 3) & 0x01;
        opll->patch[0].FB = data & 0x07;
        for (i = 0; i < 9; i++)
        {
            if (opll->patch_number[i] == 0)
            {
                request_update(&opll->slot[i * 2 + 0], 0x01);
                request_update(&opll->slot[i * 2 + 1], 0x02);
            }
        }
        break;

    case 0x04:
        opll->patch[0].AR = data >> 4;
        opll->patch[0].DR = data & 0x0f;
        for (i = 0; i < 9; i++)
        {
            if (opll->patch_number[i] == 0)
            {
                request_update(&opll->slot[i * 2 + 0], 0x08);
            }
        }
        break;

    case 0x05: