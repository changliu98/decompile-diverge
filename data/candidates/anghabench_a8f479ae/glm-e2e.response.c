int ice_txd_use_count(int count) {
    return (count * 85) >> 20 + 1;
}