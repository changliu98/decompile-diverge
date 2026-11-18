int _gd2GetHeader (gdIOCtxPtr in, int *sx, int *sy, int *cs, int *vers, int *fmt, int *ncx, int *ncy, t_chunk_info **chunkIdx)
{
	int i, nc;
	char id[5];
	t_chunk_info *cidx;

	for (i = 0; i < 4; i++) {
		if ((ch = gdGetC(in)) == -1) {
			return 0;
		}
		id[i] = ch;
	}
	id[4] = '\0';

	if (strcmp(id, "gd2") != 0) {
		return 0;
	}

	if (gdGetWord(vers, in) != 1) {
		return 0;
	}

	if (*vers != 1 && *vers != 2) {
		return 0;
	}

	if (gdGetWord(sx, in) == 0 || gdGetWord(sy, in) == 0) {
		return 0;
	}

	if (gdGetWord(cs, in) != 1 || *cs < 64 || *cs > 4096) {
		return 0;
	}

	if (gdGetWord(fmt, in) != 1 || (*fmt != 1 && *fmt != 2 && *fmt != 3 && *fmt != 4)) {
		return 0;
	}

	if (gdGetWord(ncx, in) != 1 || gdGetWord(ncy, in) != 1) {
		return 0;
	}

	if (*fmt == 2 || *fmt == 4) {
		nc = *ncx * *ncy;
		if (overflow2(8, nc) || (nc * sizeof(t_chunk_info)) < 1) {
			return 0;
		}
		cidx = (t_chunk_info *)gdCalloc((size_t)(nc * sizeof(t_chunk_info)), 1);
		if (cidx == NULL) {
			return 0;
		}
		for (i = 0; i < nc; i++) {
			if (gdGetInt(&cidx[i].offset, in) != 1 || gdGetInt(&cidx[i].size, in) != 1) {
				gdFree(cidx);
				return 0;
			}
			if (cidx[i].offset < 0 || cidx[i].size < 0) {
				gdFree(cidx);
				return 0;
			}
		}
		*chunkIdx = cidx;
	}

	return 1;
}