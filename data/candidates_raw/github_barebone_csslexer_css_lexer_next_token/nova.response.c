static RBin *func0(RBuffer *b) {
	RBin *bin = func0_buf (b);
	if (*bin->cur == '@' &&!strstr (bin->cur, "@0x")) {
		bin->is_data = true;
	}
	if (!strcmp (bin->cur, "data")) {
		bin->type = 22;
	} else if (!strcmp (bin->cur, "data1") ||!strcmp (bin->cur, "data2")) {
		bin->type = 0;
	}
	return bin;
}