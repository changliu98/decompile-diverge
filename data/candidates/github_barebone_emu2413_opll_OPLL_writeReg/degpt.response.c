void OPLL_writeReg(OPLL *opll,uint32_t reg,uint8_t data)

{
  int ch_00;
  int i;
  int ch;
  uint8_t data_local;
  uint32_t reg_local;
  OPLL *opll_local;
  
  if (reg < 0x40) {
    if ((((0x18 < reg) && (reg < 0x20)) || ((0x28 < reg && (reg < 0x30)))) ||
       ((reg_local = reg, 0x38 < reg && (reg < 0x40)))) {
      reg_local = reg - 9;
    }
    opll->reg[reg_local] = data;
    switch(reg_local) {
    case 0:
      opll->patch[0].AM = (int)(uint)data >> 7;
      opll->patch[0].PM = (int)(uint)data >> 6 & 1;
      opll->patch[0].EG = (int)(uint)data >> 5 & 1;
      opll->patch[0].KR = (int)(uint)data >> 4 & 1;
      opll->patch[0].ML = data & 0xf;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (i << 1),0xc);
        }
      }
      break;
    case 1:
      opll->patch[1].AM = (int)(uint)data >> 7;
      opll->patch[1].PM = (int)(uint)data >> 6 & 1;
      opll->patch[1].EG = (int)(uint)data >> 5 & 1;
      opll->patch[1].KR = (int)(uint)data >> 4 & 1;
      opll->patch[1].ML = data & 0xf;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (int)(i << 1 | 1),0xc);
        }
      }
      break;
    case 2:
      opll->patch[0].KL = (int)(uint)data >> 6;
      opll->patch[0].TL = data & 0x3f;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (i << 1),2);
        }
      }
      break;
    case 3:
      opll->patch[1].KL = (int)(uint)data >> 6;
      opll->patch[1].WS = (int)(uint)data >> 4 & 1;
      opll->patch[0].WS = (int)(uint)data >> 3 & 1;
      opll->patch[0].FB = data & 7;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (i << 1),1);
          request_update(opll->slot + (int)(i << 1 | 1),3);
        }
      }
      break;
    case 4:
      opll->patch[0].AR = (int)(uint)data >> 4;
      opll->patch[0].DR = data & 0xf;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (i << 1),8);
        }
      }
      break;
    case 5:
      opll->patch[1].AR = (int)(uint)data >> 4;
      opll->patch[1].DR = data & 0xf;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (int)(i << 1 | 1),8);
        }
      }
      break;
    case 6:
      opll->patch[0].SL = (int)(uint)data >> 4;
      opll->patch[0].RR = data & 0xf;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (i << 1),8);
        }
      }
      break;
    case 7:
      opll->patch[1].SL = (int)(uint)data >> 4;
      opll->patch[1].RR = data & 0xf;
      for (i = 0; i < 9; i = i + 1) {
        if (opll->patch_number[i] == 0) {
          request_update(opll->slot + (int)(i << 1 | 1),8);
        }
      }
      break;
    default:
      break;
    case 0xe:
      if (opll->chip_type != '\x01') {
        update_rhythm_mode(opll);
        update_key_status(opll);
      }
      break;
    case 0xf:
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
      set_fnumber(opll,reg_local - 0x10,
                  (uint)data + (opll->reg[(int)(reg_local + 0x10)] & 1) * 0x100);
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
      ch_00 = reg_local - 0x20;
      set_fnumber(opll,ch_00,(data & 1) * 0x100 + (uint)opll->reg[(int)(reg_local - 0x10)]);
      set_block(opll,ch_00,(int)(uint)data >> 1 & 7);
      set_sus_flag(opll,ch_00,(int)(uint)data >> 5 & 1);
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
      if (((opll->reg[0xe] & 0x20) == 0) || (reg_local < 0x36)) {
        set_patch(opll,reg_local - 0x30,(int)(uint)data >> 4);
      }
      else if (reg_local == 0x37) {
        set_slot_volume(opll->slot + 0xe,((int)(uint)data >> 4) << 2);
      }
      else if (reg_local == 0x38) {
        set_slot_volume(opll->slot + 0x10,((int)(uint)data >> 4) << 2);
      }
      set_volume(opll,reg_local - 0x30,(data & 0xf) << 2);
    }
  }
  return;
}