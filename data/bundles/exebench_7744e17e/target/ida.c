void __cdecl ee_readn(unsigned int command_ee, unsigned int *result_ee)
{
  if ( command_ee <= 0x80 )
  {
    *result_ee = 0;
    result_ee[1] = (command_ee << 8) + 229376;
  }
  else
  {
    *result_ee = 502;
  }
}