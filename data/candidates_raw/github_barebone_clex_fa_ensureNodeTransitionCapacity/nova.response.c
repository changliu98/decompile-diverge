static bool func0(struct rbsp *rbsp, size_t size)
{
	unsigned long align;
	unsigned char *realloc_buf;
	bool ret = true;

	if (!rbsp) {
		ret = false;
		goto end;
	}

	if (rbsp->size >= size) {
		ret = true;
		goto end;
	}

	if (rbsp->size)
		align = rbsp->size;
	else
		align = sizeof(long);

	while (align < size)
		align <<= 1;

	realloc_buf = realloc(rbsp->data, align);
	if (!realloc_buf) {
		ret = false;
		goto end;
	}

	memset(realloc_buf + rbsp->size, 0, align - rbsp->size);
	rbsp->data = realloc_buf;
	rbsp->size = align;
	ret = true;
end:
	return ret;
}