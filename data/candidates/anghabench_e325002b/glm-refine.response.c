const char *__cdecl xgbe_phy_speed_string(int speed)
{
  switch ( speed )
  {
    case 128:
      return "Unknown";
    case 129:
      return "2.5Gbps";
    case 130:
      return "10Gbps";
    case 131:
      return "1Gbps";
    case 132:
      return "100Mbps";
    default:
      return "Unsupported";
  }
}