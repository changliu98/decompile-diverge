static const char *xgbe_phy_speed_string(enum xgbe_phy_speed speed) {
  const char *speed_str;
  switch (speed) {
    case XGBE_PHY_SPEED_UNKNOWN:
      speed_str = "Unknown";
      break;
    case XGBE_PHY_SPEED_100:
      speed_str = "100Mbps";
      break;
    case XGBE_PHY_SPEED_1000:
      speed_str = "1Gbps";
      break;
    case XGBE_PHY_SPEED_2500:
      speed_str = "2.5Gbps";
      break;
    case XGBE_PHY_SPEED_10000:
      speed_str = "10Gbps";
      break;
    default:
      speed_str = "Unsupported";
      break;
  }
  return speed_str;
}