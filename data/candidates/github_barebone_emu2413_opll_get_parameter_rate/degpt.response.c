int get_parameter_rate(OPLL_SLOT *slot_ptr)
{
  // Return 0 if the slot is not active (type bit 0 is 0) or key is off
  if (((slot_ptr->type & 1) == 0) && (slot_ptr->key_flag == '\0')) {
    return 0;
  }
  // Determine the rate based on the current envelope generator state
  switch(slot_ptr->eg_state) {
  case '\0': // Attack state
    return slot_ptr->patch->AR;
  case '\x01': // Decay state
    return slot_ptr->patch->DR;
  case '\x02': // Sustain state
    // If EG mode is 0, return Rate Ramp (RR), otherwise return 0
    return slot_ptr->patch->EG == 0 ? slot_ptr->patch->RR : 0;
  case '\x03': // Release state
    if (slot_ptr->sus_flag == '\0') {
      // If not in sustain mode, return 7 if EG mode is 0, otherwise return RR
      return slot_ptr->patch->EG == 0 ? 7 : slot_ptr->patch->RR;
    }
    else {
      // If in sustain mode, return fixed rate 5
      return 5;
    }
  case '\x04': // Off state
    return 0xc;
  default:
    return 0;
  }
}