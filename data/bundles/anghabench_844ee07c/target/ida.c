int __cdecl cvmx_helper_get_ipd_port(int interface, int port)
{
  int v3; // [rsp+14h] [rbp-4h]

  switch ( interface )
  {
    case 0:
      v3 = port;
      break;
    case 1:
      v3 = port + 16;
      break;
    case 2:
      v3 = port + 32;
      break;
    case 3:
      v3 = port + 36;
      break;
    case 4:
      v3 = port + 40;
      break;
    case 5:
      v3 = port + 44;
      break;
    default:
      v3 = -1;
      break;
  }
  return v3;
}