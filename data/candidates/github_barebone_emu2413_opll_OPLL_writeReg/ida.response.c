void __cdecl OPLL_writeReg(OPLL *opll, uint32_t reg, uint8_t data)
{
  int i; // [rsp+18h] [rbp-18h]
  int ia; // [rsp+18h] [rbp-18h]
  int ib; // [rsp+18h] [rbp-18h]
  int ic; // [rsp+18h] [rbp-18h]
  int id; // [rsp+18h] [rbp-18h]
  int ie; // [rsp+18h] [rbp-18h]
  int ig; // [rsp+18h] [rbp-18h]
  int ih; // [rsp+18h] [rbp-18h]
  uint32_t rega; // [rsp+24h] [rbp-Ch]

  rega = reg;
  if ( reg < 0x40 )
  {
    if ( reg >= 0x19 && reg <= 0x1F || reg >= 0x29 && reg <= 0x2F || reg >= 0x39 )
      rega = reg - 9;
    opll->reg[rega] = data;
    switch ( rega )
    {
      case 0u:
        opll->patch[0].AM = ((int)data >> 7) & 1;
        opll->patch[0].PM = ((int)data >> 6) & 1;
        opll->patch[0].EG = ((int)data >> 5) & 1;
        opll->patch[0].KR = ((int)data >> 4) & 1;
        opll->patch[0].ML = data & 0xF;
        for ( i = 0; i < 9; ++i )
        {
          if ( !opll->patch_number[i] )
            request_update(&opll->slot[2 * i], 12);
        }
        break;
      case 1u:
        opll->patch[1].AM = ((int)data >> 7) & 1;
        opll->patch[1].PM = ((int)data >> 6) & 1;
        opll->patch[1].EG = ((int)data >> 5) & 1;
        opll->patch[1].KR = ((int)data >> 4) & 1;
        opll->patch[1].ML = data & 0xF;
        for ( ia = 0; ia < 9; ++ia )
        {
          if ( !opll->patch_number[ia] )
            request_update(&opll->slot[(2 * ia) | 1], 12);
        }
        break;
      case 2u:
        opll->patch[0].KL = ((int)data >> 6) & 3;
        opll->patch[0].TL = data & 0x3F;
        for ( ib = 0; ib < 9; ++ib )
        {
          if ( !opll->patch_number[ib] )
            request_update(&opll->slot[2 * ib], 2);
        }
        break;
      case 3u:
        opll->patch[1].KL = ((int)data >> 6) & 3;
        opll->patch[1].WS = ((int)data >> 4) & 1;
        opll->patch[0].WS = ((int)data >> 3) & 1;
        opll->patch[0].FB = data & 7;
        for ( ic = 0; ic < 9; ++ic )
        {
          if ( !opll->patch_number[ic] )
          {
            request_update(&opll->slot[2 * ic], 1);
            request_update(&opll->slot[(2 * ic) | 1], 3);
          }
        }
        break;
      case 4u:
        opll->patch[0].AR = ((int)data >> 4) & 0xF;
        opll->patch[0].DR = data & 0xF;
        for ( id = 0; id < 9; ++id )
        {
          if ( !opll->patch_number[id] )
            request_update(&opll->slot[2 * id], 8);
        }
        break;
      case 5u:
        opll->patch[1].AR = ((int)data >> 4) & 0xF;
        opll->patch[1].DR = data & 0xF;
        for ( ie = 0; ie < 9; ++ie )
        {
          if ( !opll->patch_number[ie] )
            request_update(&opll->slot[(2 * ie) | 1], 8);
        }
        break;
      case 6u:
        opll->patch[0].SL = ((int)data >> 4) & 0xF;
        opll->patch[0].RR = data & 0xF;
        for ( ig = 0; ig < 9; ++ig )
        {
          if ( !opll->patch_number[ig] )
            request_update(&opll->slot[2 * ig], 8);
        }
        break;
      case 7u:
        opll->patch[1].SL = ((int)data >> 4) & 0xF;
        opll->patch[1].RR = data & 0xF;
        for ( ih = 0; ih < 9; ++ih )
        {
          if ( !opll->patch_number[ih] )
            request_update(&opll->slot[(2 * ih) | 1], 8);
        }
        break;
      case 0xEu:
        if ( opll->chip_type != 1 )
        {
          update_rhythm_mode(opll);
          update_key_status(opll);
        }
        break;
      case 0xFu:
        opll->test_flag = data;
        break;
      case 0x10u:
      case 0x11u:
      case 0x12u:
      case 0x13u:
      case 0x14u:
      case 0x15u:
      case 0x16u:
      case 0x17u:
      case 0x18u:
        set_fnumber(opll, rega - 16, ((opll->reg[rega - 16 + 32] & 1) << 8) + data);
        break;
      case 0x20u:
      case 0x21u:
      case 0x22u:
      case 0x23u:
      case 0x24u:
      case 0x25u:
      case 0x26u:
      case 0x27u:
      case 0x28u:
        set_fnumber(opll, rega - 32, opll->reg[rega - 32 + 16] + ((data & 1) << 8));
        set_block(opll, rega - 32, ((int)data >> 1) & 7);
        set_sus_flag(opll, rega - 32, ((int)data >> 5) & 1);
        update_key_status(opll);
        break;
      case 0x30u:
      case 0x31u:
      case 0x32u:
      case 0x33u:
      case 0x34u:
      case 0x35u:
      case 0x36u:
      case 0x37u:
      case 0x38u:
        if ( (opll->reg[14] & 0x20) != 0 && rega >= 0x36 )
        {
          if ( rega == 55 )
          {
            set_slot_volume(&opll->slot[14], 4 * (((int)data >> 4) & 0xF));
          }
          else if ( rega == 56 )
          {
            set_slot_volume(&opll->slot[16], 4 * (((int)data >> 4) & 0xF));
          }
        }
        else
        {
          set_patch(opll, rega - 48, ((int)data >> 4) & 0xF);
        }
        set_volume(opll, rega - 48, 4 * (data & 0xF));
        break;
      default:
        return;
    }
  }
}