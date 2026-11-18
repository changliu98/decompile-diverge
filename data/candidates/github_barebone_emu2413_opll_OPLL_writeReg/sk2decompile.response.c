void OPLL_writeReg(OPLL *opll, int reg, int data) {
  int i;
  if (reg < 0x40) {
    if ((reg >= 0x19 && reg <= 0x1f) || (reg >= 0x29 && reg <= 0x2f) ||
        reg >= 0x39) {
      reg -= 9;
    }
    opll->reg[reg] = data;
    switch (reg) {
      case 0x00:
        opll->ch[0].test = (data >> 7) & 1;
        opll->ch[0].ml = (data >> 6) & 1;
        opll->ch[0].am = (data >> 5) & 1;
        opll->ch[0].kr = (data >> 4) & 1;
        opll->ch[0].ks = data & 0x0f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2], 0x0c);
          }
        }
        break;
      case 0x01:
        opll->ch[1].test = (data >> 7) & 1;
        opll->ch[1].ml = (data >> 6) & 1;
        opll->ch[1].am = (data >> 5) & 1;
        opll->ch[1].kr = (data >> 4) & 1;
        opll->ch[1].ks = data & 0x0f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2 + 1], 0x0c);
          }
        }
        break;
      case 0x02:
        opll->ch[0].fbl = (data >> 6) & 3;
        opll->ch[0].tll = data & 0x3f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2], 0x02);
          }
        }
        break;
      case 0x03:
        opll->ch[1].fbl = (data >> 6) & 3;
        opll->ch[0].ebit = (data >> 3) & 1;
        opll->ch[1].ebit = (data >> 4) & 1;
        opll->ch[0].fnum = data & 7;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2], 0x01);
            request_update(&opll->slot[i * 2 + 1], 0x03);
          }
        }
        break;
      case 0x04:
        opll->ch[0].tl = (data >> 4) & 0x0f;
        opll->ch[0].ksr = data & 0x0f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2], 0x08);
          }
        }
        break;
      case 0x05:
        opll->ch[1].tl = (data >> 4) & 0x0f;
        opll->ch[1].ksr = data & 0x0f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2 + 1], 0x08);
          }
        }
        break;
      case 0x06:
        opll->ch[0].volume = (data >> 4) & 0x0f;
        opll->ch[0].multiple = data & 0x0f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2], 0x08);
          }
        }
        break;
      case 0x07:
        opll->ch[1].volume = (data >> 4) & 0x0f;
        opll->ch[1].multiple = data & 0x0f;
        for (i = 0; i < 9; i++) {
          if (opll->slot_status[i] == 0) {
            request_update(&opll->slot[i * 2 + 1], 0x08);
          }
        }
        break;
      case 0x0e:
        if (opll->rhythm_mode != 1) {
          update_rhythm_mode(opll);
          update_key_status(opll);
        }
        break;
      case 0x0f:
        opll->noise = data;
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
        set_fnumber(opll, reg - 0x10,
                    (opll->reg[reg - 0x10 + 0x20] & 1) * 256 + data);
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
        set_fnumber(opll, reg - 0x20,
                    opll->reg[reg - 0x20 + 0x10] + ((data & 1) * 256));
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
        if ((opll->reg[0x0e] & 0x20) && reg >= 0x36) {
          if (reg == 0x37) {
            set_slot_volume(&opll->slot[0x0e], (data >> 4) & 0x0f);
          } else if (reg == 0x38) {
            set_slot_volume(&opll->slot[0x10], (data >> 4) & 0x0f);
          }
        } else {
          set_patch(opll, reg - 0x30, (data >> 4) & 0x0f);
        }
        set_volume(opll, reg - 0x30, (data & 0x0f) * 4);
        break;
    }
  }
}