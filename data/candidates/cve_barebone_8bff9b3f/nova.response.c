static const char *bittok2str_internal(struct mem_ctl_info *mci,
					struct csrow_info *csrow,
					u64 sys_addr, const char *mc_type)
{
	static char buf[256];
	int len = 0;
	unsigned int chan, x;
	u64 addr;

	while (1) {
		if (!mci ||!mci->csrows)
			break;

		addr = mci->csrows->base_addr;
		chan = 1;
		while (chan) {
			if (sys_addr == (addr & ~0xFFFFULL)) {
				len += scnprintf(buf + len, sizeof(buf) - len,
						 "[%s%u] ", mc_type, chan);
				sys_addr = addr;
				break;
			}
			chan <<= 1;
		}
		mci++;
	}

	if (len == 0) {
		if (!csrow)
			csrow = &csrow_info[0];
		x = csrow->first_page;
		len += scnprintf(buf + len, sizeof(buf) - len,
				 "[%s%u] ", mc_type, x);
	}

	return buf;
}