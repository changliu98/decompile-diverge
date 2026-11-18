int bitsToIp4AddrArr(uint ipAddress, int *octets)
{
  // Extract the first octet (most significant 8 bits)
  *octets = ipAddress >> 0x18;
  // Extract the second octet (bits 16-23)
  octets[1] = (ipAddress & 0xff0000) >> 0x10;
  // Extract the third octet (bits 8-15)
  octets[2] = (ipAddress & 0xff00) >> 8;
  // Extract the fourth octet (least significant 8 bits)
  octets[3] = ipAddress & 0xff;
  return 0;
}