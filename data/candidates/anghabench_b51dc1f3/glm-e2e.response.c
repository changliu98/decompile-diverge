int get_sorting_mode(int index) {
    if (index < 0 || index >= 128) {
        return -1;
    }
    return tbl_sorting_mode[index];
}