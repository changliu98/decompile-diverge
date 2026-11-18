long long FS460_get_available_vga_modes(long long *modes) {
    long long ret;
    
    if (modes == 0) {
        ret = 0x1000;
    } else {
        *modes = 0x1f;
        ret = 0;
    }
    
    return ret;
}