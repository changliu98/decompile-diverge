/*
 * Map a WiFi rate value to its corresponding index in the rate table.
 *
 * Parameters:
 *   rate - The raw rate value (lower 7 bits are used for lookup).
 *
 * Returns:
 *   The index in the rate table corresponding to the given rate.
 *   Returns 0 if the rate is not found in the table.
 */
int wifirate2_ratetbl_inx(uchar raw_rate_value)
{
    /* Mask out the upper bit to get the base rate value */
    switch(raw_rate_value & 0x7f) {
    case 2: return 0;   /* Rate 2 Mbps -> Index 0 */
    case 4: return 1;   /* Rate 4 Mbps -> Index 1 */
    case 0xb: return 2; /* Rate 11 Mbps -> Index 2 */
    case 0xc: return 4; /* Rate 12 Mbps -> Index 4 */
    case 0x12: return 5;/* Rate 18 Mbps -> Index 5 */
    case 0x16: return 3;/* Rate 24 Mbps -> Index 3 */
    case 0x18: return 6;/* Rate 36 Mbps -> Index 6 */
    case 0x24: return 7;/* Rate 48 Mbps -> Index 7 */
    case 0x30: return 8;/* Rate 54 Mbps -> Index 8 */
    case 0x48: return 9;/* Rate 72 Mbps -> Index 9 */
    case 0x60: return 10;/* Rate 96 Mbps -> Index 10 */
    case 0x6c: return 0xb;/* Rate 108 Mbps -> Index 11 */
    }
    /* Default return for unrecognized rates */
    return 0;
}