char *xgbe_phy_speed_string(int speed)
{
	char *str;

	switch (speed) {
	case SPEED_100:
		str = "100Mbps";
		break;
	case SPEED_1000:
		str = "1Gbps";
		break;
	case SPEED_2500:
		str = "2.5Gbps";
		break;
	case SPEED_10000:
		str = "10Gbps";
		break;
	case SPEED_UNKNOWN:
		str = "Unknown";
		break;
	default:
		str = "Unsupported";
	}

	return str;
}