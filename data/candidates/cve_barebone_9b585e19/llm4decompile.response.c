int
archive_read_format_rar_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	int ret;
	struct rar *rar = (struct rar *)(a->format->data);

	if (rar->file.compressed_size == -1)
		rar->file.compressed_size = 0;

	if (rar->entry_offset > 0) {
		__archive_read_consume(a, rar->entry_offset);
		rar->entry_offset = 0;
	}

	*buff = NULL;
	if (rar->file.file.IsDir || rar->file.file.Size >= rar->file.uncompressed_size) {
		*size = 0;
		*offset = rar->file.file.FilePos;
		if (*offset < rar->file.uncompressed_size)
			*offset = rar->file.uncompressed_size;
		return (1);
	}

	if (rar->file.file.Method == 0x30)
		ret = read_data_stored(a, buff, size, offset);
	else if (rar->file.file.Method >= 0x31 && rar->file.file.Method <= 0x35)
		ret = read_data_compressed(a, buff, size, offset);
	else {
		archive_set_error(&a->archive, -1,
		    "Unsupported compression method for RAR file.");
		ret = -30;
	}

	if (ret != 0 && ret != -20)
		__archive_ppmd7_functions.Ppmd7_Free(&rar->ppmd);

	return (ret);
}