static bool __attribute__((noinline)) MACH0_(struct obj_t *bin, ut32 offset, ut32 size) {
	bool r = parse_chained_fixups(bin, offset, size);
	g_no_tailcall_sink += 1;
	return r;
}