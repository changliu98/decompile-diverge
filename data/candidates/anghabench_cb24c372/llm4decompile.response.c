bool alps_check_valid_firmware_id(unsigned char *id)
{

 if (id[0] == 0x73)
  return true;


 if (id[0] != 0x88)
  return false;


 if (id[1] == 0x07 || id[1] == 0x08)
  return true;


 if ((id[1] & 0xF0) == 0xB0)
  return true;


 if ((id[1] & 0xF0) == 0xC0)
  return true;

 return false;
}