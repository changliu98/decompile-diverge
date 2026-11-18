const char *xgbe_phy_speed_string(int speed) {
    const char *ret;

    switch (speed) {
        case 0:
            ret = "1 Gbps"; // 0x2018
            break;
        case 1:
            ret = "10 Gbps"; // 0x2020
            break;
        case 2:
            ret = "2.5 Gbps"; // 0x2026
            break;
        case 3:
            ret = "25 Gbps"; // 0x202e
            break;
        case 4:
            ret = "40 Gbps"; // 0x2035
            break;
        default:
            ret = "Unknown !"; // 0x203d
            break;
    }

    return ret;
}