char *xgbe_phy_speed_string(int speed)
{
 char *speed_str = ((void *)0);
 switch (speed) {
  case 128:
   speed_str = "Unknown";
   break;
  case 129:
   speed_str = "2.5Gbps";
   break;
  case 130:
   speed_str = "10Gbps";
   break;
  case 131:
   speed_str = "1Gbps";
   break;
  case 132:
   speed_str = "100Mbps";
   break;
  default:
   speed_str = "Unsupported";
   break;
 }
 return speed_str;
}