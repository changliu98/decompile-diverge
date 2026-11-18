bool alps_check_valid_firmware_id(uchar *id)

{
  uchar *id_local;
  bool local_c;
  
  if (*id == 's') {
    local_c = 1;
  }
  else if ((*id == 0x88) &&
          ((((id[1] == '\a' || (id[1] == '\b')) || ((id[1] & 0xf0) == 0xb0)) ||
           ((id[1] & 0xf0) == 0xc0)))) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return local_c;
}