int _gd2GetHeader (gdIOCtxPtr in, int *sx, int *sy, int *cs, int *vers, int *fmt, int *ncx, int *ncy, t_chunk_info **chunkIdx)
{
	int size;
	char id[5];
	int i;
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

	if (gdGetWord(sx, in) == 0) {
		return 0;
	}

	if (gdGetWord(sy, in) == 0) {
		return 0;
	}

	if (gdGetWord(cs, in) != 1) {
		return 0;
	}

	if (*cs < 64 || *cs > 4096) {
		return 0;
	}

	if (gdGetWord(fmt, in) != 1) {
		return 0;
	}

	if (*fmt != 1 && *fmt != 2 && *fmt != 3 && *fmt != 4) {
		return 0;
	}

	if (gdGetWord(ncx, in) != 1) {
		return 0;
	}

	if (gdGetWord(ncy, in) != 1) {
		return 0;
	}

	if (*fmt == 2 || *fmt == 4) {
		size = *ncx * *ncy * sizeof(t_chunk_info);
		if (size <= 0) {
			return 0;
		}
		cidx = (t_chunk_info *) calloc(size, 1);
		for (i = 0; i < *ncx * *ncy; i++) {
			if (gdGetInt(&cidx[i].offset, in) != 1) {
				free(cidx);
				return 0;
			}
			if (gdGetInt(&cidx[i].size, in) != 1) {
				free(cidx);
				return 0;
			}
			if (cidx[i].offset < 0 || cidx[i].size < 0) {
				free(cidx);
				return 0;
			}
		}
		*chunkIdx = cidx;
	}

	return 1;
}