char *gdb_to_rz_profile(const char *gdb) {
	RzStrBuf *sb;
	char name[16];
	char type[16];
	char groups[128];
	int number;
	int rel;
	int offset;
	int size;
	int ret;
	int all;
	int gpr;
	int save;
	int restore;
	int float_;
	int sse;
	int mmx;
	int vector;
	int system;
	char *ptr;
	char *gptr;
	char *gptr1;
	char *ptr1;
	char *local_gdb;

	if (!gdb) {
		return NULL;
	}
	sb = rz_strbuf_new ("");
	if (!sb) {
		return NULL;
	}
	all = 1;
	gpr = 2;
	save = 4;
	restore = 8;
	float_ = 16;
	sse = 32;
	vector = 64;
	system = 128;
	mmx = 256;
	ptr = rz_str_trim_head_ro (gdb);
	if (rz_str_startswith (ptr, "Name")) {
		ptr = strchr (ptr, '\n');
		if (!ptr) {
			rz_strbuf_free (sb);
			return NULL;
		}
		ptr++;
	}
	while (1) {
		while (isspace ((int)*ptr)) {
			ptr++;
		}
		if (!*ptr) {
			break;
		}
		ptr1 = strchr (ptr, '\n');
		if (!ptr1) {
			fprintf (stderr, "Could not parse line: %s (missing \\n)\n", ptr);
			rz_strbuf_free (sb);
			return NULL;
		}
		*ptr1 = 0;
		ret = __isoc99_sscanf (ptr, " %s %d %d %d %d %s %s", name, &number, &rel, &offset, &size, type, groups);
		if (ret < 6) {
			if (*ptr == '*') {
				ptr = ptr1 + 1;
				continue;
			}
			fprintf (stderr, "Could not parse line: %s\n", ptr);
			rz_strbuf_free (sb);
			return NULL;
		}
		if (rz_str_startswith (name, "''")) {
			if (!ptr1) {
				break;
			}
			ptr = ptr1 + 1;
			continue;
		}
		if (!size) {
			if (!ptr1) {
				break;
			}
			ptr = ptr1 + 1;
			continue;
		}
		float_ = 0;
		sse = 0;
		mmx = 0;
		vector = 0;
		system = 0;
		if (ret > 6) {
			gptr = groups;
			while (1) {
				gptr1 = strchr (gptr, ',');
				if (gptr1) {
					*gptr1 = 0;
				}
				if (rz_str_startswith (gptr, "general")) {
					gpr = all;
				} else if (rz_str_startswith (gptr, "all")) {
					gpr = all;
				} else if (rz_str_startswith (gptr, "save")) {
					save = all;
				} else if (rz_str_startswith (gptr, "restore")) {
					restore = all;
				} else if (rz_str_startswith (gptr, "float")) {
					float_ = all;
				} else if (rz_str_startswith (gptr, "sse")) {
					sse = all;
				} else if (rz_str_startswith (gptr, "mmx")) {
					mmx = all;
				} else if (rz_str_startswith (gptr, "vector")) {
					vector = all;
				} else if (rz_str_startswith (gptr, "system")) {
					system = all;
				}
				if (!gptr1) {
					break;
				}
				gptr = gptr1 + 1;
			}
		}
		if (!type[0]) {
			if (!ptr1) {
				break;
			}
			ptr = ptr1 + 1;
			continue;
		}
		rz_strbuf_appendf (sb, "%s\t%s\t.%d\t%d\t0\n",
			float_ || sse || mmx || vector || system ? "fpu" : "gpr",
			name, size * 8, offset);
		if (!ptr1) {
			break;
		}
		ptr = ptr1 + 1;
	}
	return rz_strbuf_drain (sb);
}