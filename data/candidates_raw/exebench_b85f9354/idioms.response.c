void updateCRC(char *crc, char newval)
{
  *crc ^= newval;
}