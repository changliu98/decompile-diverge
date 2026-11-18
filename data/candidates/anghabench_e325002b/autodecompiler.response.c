__attribute__((used)) static char *xgbe_phy_speed_string(int speed)
{
	char *desc;

	switch (speed) {
	case SPEED_100:
		desc = "100Mbps";
		break;
	case SPEED_1000:
		desc = "1Gbps";
		break;
	case SPEED_2500:
		desc = "2.5Gbps";
		break;
	case SPEED_10000:
		desc = "10Gbps";
		break;
	case SPEED_UNKNOWN:
		desc = "Unknown";
		break;
	default:
		desc = "Unsupported";
	}

	return desc;
}