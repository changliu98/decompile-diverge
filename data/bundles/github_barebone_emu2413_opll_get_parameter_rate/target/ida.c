int __cdecl get_parameter_rate(OPLL_SLOT *slot)
{
  uint32_t RR; // [rsp+0h] [rbp-1Ch]
  int AR; // [rsp+18h] [rbp-4h]

  if ( (slot->type & 1) == 0 && !slot->key_flag )
    return 0;
  switch ( slot->eg_state )
  {
    case 0u:
      AR = slot->patch->AR;
      break;
    case 1u:
      AR = slot->patch->DR;
      break;
    case 2u:
      if ( slot->patch->EG )
        RR = 0;
      else
        RR = slot->patch->RR;
      AR = RR;
      break;
    case 3u:
      if ( slot->sus_flag )
      {
        AR = 5;
      }
      else if ( slot->patch->EG )
      {
        AR = slot->patch->RR;
      }
      else
      {
        AR = 7;
      }
      break;
    case 4u:
      AR = 12;
      break;
    default:
      AR = 0;
      break;
  }
  return AR;
}