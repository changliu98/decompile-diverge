static unsigned char fsp_test_invert_cmd(unsigned char bcd)
{
  if (bcd == 0xe9 || bcd == 0xee || bcd == 0xf2 || bcd == 0xff)
    return (unsigned char)(0xff - bcd);
  else
    return bcd;
}