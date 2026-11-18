int ad7192_get_temp_scale(int temp) {
    if (temp != 0) {
        return 0x15fe;
    } else {
        return 0xaff;
    }
}