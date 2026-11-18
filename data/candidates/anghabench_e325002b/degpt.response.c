/*
 * xgbe_phy_speed_string - Convert PHY speed code to human-readable string
 *
 * @speed: The speed code value to convert
 *
 * Returns a static string representing the speed, or "Unknown"/"Unsupported"
 * if the speed code is not recognized.
 */
char * xgbe_phy_speed_string(int speed_code)
{
	switch(speed_code) {
	case 0x80:
		return "Unknown";
	case 0x81:
		return "2.5Gbps";
	case 0x82:
		return "10Gbps";
	case 0x83:
		return "1Gbps";
	case 0x84:
		return "100Mbps";
	default:
		return "Unsupported";
	}
}