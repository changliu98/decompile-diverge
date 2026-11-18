const char *__cdecl xgbe_phy_speed_string(int speed)
{
  const char *v2; // [rsp+10h] [rbp-8h]

  switch ( speed )
  {
    case 128:
      v2 = "Unknown";
      break;
    case 129:
      v2 = "2.5Gbps";
      break;
    case 130:
      v2 = "10Gbps";
      break;
    case 131:
      v2 = "1Gbps";
      break;
    case 132:
      v2 = "100Mbps";
      break;
    default:
      v2 = "Unsupported";
      break;
  }
  return v2;
}