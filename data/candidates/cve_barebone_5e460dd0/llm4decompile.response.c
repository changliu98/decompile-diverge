bool MACH0_(obj_t *bin, ut32 offset, ut32 size) {
	bool ret = parse_chained_fixups (bin, offset, size);
	g_no_tailcall_sink++;
	return ret;
}