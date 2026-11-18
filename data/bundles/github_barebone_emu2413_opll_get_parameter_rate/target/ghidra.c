int get_parameter_rate(OPLL_SLOT *slot)

{
  uint32_t local_24;
  OPLL_SLOT *slot_local;
  uint32_t local_c;
  
  if (((slot->type & 1) == 0) && (slot->key_flag == '\0')) {
    local_c = 0;
  }
  else {
    switch(slot->eg_state) {
    case '\0':
      local_c = slot->patch->AR;
      break;
    case '\x01':
      local_c = slot->patch->DR;
      break;
    case '\x02':
      if (slot->patch->EG == 0) {
        local_24 = slot->patch->RR;
      }
      else {
        local_24 = 0;
      }
      local_c = local_24;
      break;
    case '\x03':
      if (slot->sus_flag == '\0') {
        if (slot->patch->EG == 0) {
          local_c = 7;
        }
        else {
          local_c = slot->patch->RR;
        }
      }
      else {
        local_c = 5;
      }
      break;
    case '\x04':
      local_c = 0xc;
      break;
    default:
      local_c = 0;
    }
  }
  return local_c;
}