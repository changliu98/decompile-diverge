int sht21_temp_ticks_to_millicelsius(int ticks) {
    ticks &= ~0x3; // Equivalent to ticks & 0xfffffffc
    return (ticks * 0x55cd >> 13) - 0xb702;
}