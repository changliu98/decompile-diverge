int cvmx_helper_get_ipd_port(int interface,int port)

{
  int port_local;
  int interface_local;
  int local_c;
  
  switch(interface) {
  case 0:
    local_c = port;
    break;
  case 1:
    local_c = port + 0x10;
    break;
  case 2:
    local_c = port + 0x20;
    break;
  case 3:
    local_c = port + 0x24;
    break;
  case 4:
    local_c = port + 0x28;
    break;
  case 5:
    local_c = port + 0x2c;
    break;
  default:
    local_c = -1;
  }
  return local_c;
}