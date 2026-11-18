bool alps_check_valid_firmware_id(uchar *firmwareId)
{
  // Check if the firmware ID starts with 's'
  if (*firmwareId == 's') {
    return true;
  }
  // Check if the firmware ID starts with 0x88 and the second byte matches specific patterns
  if ((*firmwareId == 0x88) &&
      (((firmwareId[1] == '\a' || (firmwareId[1] == '\b')) || ((firmwareId[1] & 0xf0) == 0xb0)) ||
       ((firmwareId[1] & 0xf0) == 0xc0))) {
    return true;
  }
  // Return false if none of the conditions are met
  return false;
}