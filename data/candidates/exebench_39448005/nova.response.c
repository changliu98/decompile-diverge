static int FS460_get_available_vga_modes(ut8 *al) {
	if (!al) {
		int ret = 4096;
		*al = 31;
		return ret;
	}
	return 0;
}