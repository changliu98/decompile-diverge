void __cdecl OPLL_writeReg(OPLL *opll, uint32_t reg, uint8_t data)
{
  int i;

  if (reg >= 0x40)
    return;

  // Map rhythm channels to their melodic equivalents
  if ((reg >= 0x19 && reg <= 0x1F) || (reg >= 0x29 && reg <= 0x2F) || reg >= 0x39)
    reg -= 9;

  opll->reg[reg] = data;

  switch (reg)
  {
    case 0x00:
      opll->patch[0].AM = (data >> 7) & 1;
      opll->patch[0].PM = (data >> 6) & 1;
      opll->patch[0].EG = (data >> 5) & 1;
      opll->patch[0].KR = (data >> 4) & 1;
      opll->patch[0].ML = data & 0xF;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[2 * i], 12);
      break;

    case 0x01:
      opll->patch[1].AM = (data >> 7) & 1;
      opll->patch[1].PM = (data >> 6) & 1;
      opll->patch[1].EG = (data >> 5) & 1;
      opll->patch[1].KR = (data >> 4) & 1;
      opll->patch[1].ML = data & 0xF;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[(2 * i) | 1], 12);
      break;

    case 0x02:
      opll->patch[0].KL = (data >> 6) & 3;
      opll->patch[0].TL = data & 0x3F;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[2 * i], 2);
      break;

    case 0x03:
      opll->patch[1].KL = (data >> 6) & 3;
      opll->patch[1].WS = (data >> 4) & 1;
      opll->patch[0].WS = (data >> 3) & 1;
      opll->patch[0].FB = data & 7;
      for (i = 0; i < 9; ++i)
      {
        if (!opll->patch_number[i])
        {
          request_update(&opll->slot[2 * i], 1);
          request_update(&opll->slot[(2 * i) | 1], 3);
        }
      }
      break;

    case 0x04:
      opll->patch[0].AR = (data >> 4) & 0xF;
      opll->patch[0].DR = data & 0xF;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[2 * i], 8);
      break;

    case 0x05:
      opll->patch[1].AR = (data >> 4) & 0xF;
      opll->patch[1].DR = data & 0xF;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[(2 * i) | 1], 8);
      break;

    case 0x06:
      opll->patch[0].SL = (data >> 4) & 0xF;
      opll->patch[0].RR = data & 0xF;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[2 * i], 8);
      break;

    case 0x07:
      opll->patch[1].SL = (data >> 4) & 0xF;
      opll->patch[1].RR = data & 0xF;
      for (i = 0; i < 9; ++i)
        if (!opll->patch_number[i])
          request_update(&opll->slot[(2 * i) | 1], 8);
      break;

    case 0x0E:
      if (opll->chip_type != 1)
      {
        update_rhythm_mode(opll);
        update_key_status(opll);
      }
      break;

    case 0x0F:
      opll->test_flag = data;
      break;

    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
      set_fnumber(opll, reg - 0x10, ((opll->reg[reg - 0x10 + 0x20] & 1) << 8) + data);
      break;

    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
      set_fnumber(opll, reg - 0x20, opll->reg[reg - 0x20 + 0x10] + ((data & 1) << 8));
      set_block(opll, reg - 0x20, (data >> 1) & 7);
      set_sus_flag(opll, reg - 0x20, (data >> 5) & 1);
      update_key_status(opll);
      break;

    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
      if ((opll->reg[0x0E] & 0x20) != 0 && reg >= 0x36)
      {
        if (reg == 0x37)
          set_slot_volume(&opll->slot[14], 4 * ((data >> 4) & 0xF));
        else if (reg == 0x38)
          set_slot_volume(&opll->slot[16], 4 * ((data >> 4) & 0xF));
      }
      else
      {
        set_patch(opll, reg - 0x30, (data >> 4) & 0xF);
      }
      set_volume(opll, reg - 0x30, 4 * (data & 0xF));
      break;

    default:
      return;
  }
}