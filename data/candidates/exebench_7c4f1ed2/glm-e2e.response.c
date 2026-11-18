void decode_dir(int16_t dir, int *low, int *high) {
    *low = (dir & 0xFF) - 2;
    *high = ((dir & 0xFF00) >> 8) - 2;
}