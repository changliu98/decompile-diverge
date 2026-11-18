int get_parameter_rate(struct opll_slot *slot)
{
  int ar;
  if ( (slot->type & 1) == 0 && !slot->key_flag )
    return 0;
  switch ( slot->eg_state )
  {
    case 0:
      ar = slot->patch->AR;
      break;
    case 1:
      ar = slot->patch->DR;
      break;
    case 2:
      if ( slot->patch->EG )
        ar = 0;
      else
        ar = slot->patch->RR;
      break;
    case 3:
      if ( slot->sus_flag )
        ar = 5;
      else
      {
        if ( slot->patch->EG )
          ar = slot->patch->RR;
        else
          ar = 7;
      }
      break;
    case 4:
      ar = 12;
      break;
    default:
      ar = 0;
      break;
  }
  return ar;
}