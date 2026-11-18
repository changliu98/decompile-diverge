int __cdecl I2CSensor_Read(
        int *bus,
        unsigned __int8 I2CAddress,
        unsigned __int8 registry,
        unsigned __int8 *buffer,
        int size)
{
  unsigned __int8 registrya; // [rsp+1Eh] [rbp-12h] BYREF
  unsigned __int8 I2CAddressa; // [rsp+1Fh] [rbp-11h]
  int *busa; // [rsp+20h] [rbp-10h]

  busa = bus;
  I2CAddressa = I2CAddress;
  registrya = registry;
  if ( ioctl(*bus, 0x703uLL, I2CAddress) < 0 )
    return 3;
  if ( write(*busa, &registrya, 1uLL) != 1 )
    return 3;
  if ( read(*busa, buffer, size) == size )
    return 0;
  return 3;
}