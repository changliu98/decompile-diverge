char * xgbe_phy_speed_string(int speed)

{
  int speed_local;
  char *local_10;
  
  switch(speed) {
  case 0x80:
    local_10 = "Unknown";
    break;
  case 0x81:
    local_10 = "2.5Gbps";
    break;
  case 0x82:
    local_10 = "10Gbps";
    break;
  case 0x83:
    local_10 = "1Gbps";
    break;
  case 0x84:
    local_10 = "100Mbps";
    break;
  default:
    local_10 = "Unsupported";
  }
  return local_10;
}