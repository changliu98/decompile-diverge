int __cdecl wifi_rate_to_rate_tbl_index(unsigned __int8 rate)
{
    // Mask out the basic rate bit (Bit 7) to get the raw rate value
    switch (rate & 0x7F)
    {
        case 2:   // 1 Mbps
            return 0;
        case 4:   // 2 Mbps
            return 1;
        case 11:  // 5.5 Mbps
            return 2;
        case 22:  // 11 Mbps
            return 3;
        case 12:  // 6 Mbps
            return 4;
        case 18:  // 9 Mbps
            return 5;
        case 24:  // 12 Mbps
            return 6;
        case 36:  // 18 Mbps
            return 7;
        case 48:  // 24 Mbps
            return 8;
        case 72:  // 36 Mbps
            return 9;
        case 96:  // 48 Mbps
            return 10;
        case 108: // 54 Mbps
            return 11;
        default:
            return 0; // Unknown rate defaults to index 0
    }
}