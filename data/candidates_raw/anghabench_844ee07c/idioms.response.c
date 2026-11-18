int get_port(int interface, int port)
{
  int port_num = -1;
  switch (interface)
  {
    case 0:
      port_num = port;
      break;
    case 1:
      port_num = port + 16;
      break;
    case 2:
      port_num = port + 32;
      break;
    case 3:
      port_num = port + 36;
      break;
    case 4:
      port_num = port + 40;
      break;
    case 5:
      port_num = port + 44;
      break;
    default:
      port_num = -1;
      break;
  }
  return (port_num);
}