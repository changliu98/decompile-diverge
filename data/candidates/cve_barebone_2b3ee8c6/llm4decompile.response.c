int
zip_read_mac_metadata(struct archive_read *a, struct archive_entry *entry,
    struct zip_entry *rsrc)
{
	int64_t offset;
	unsigned char *metadata;
	unsigned char *mp;
	size_t remaining_bytes;
	size_t metadata_bytes;
	ssize_t bytes_avail, hsize;
	int ret, eof;
	struct zip *zip = (struct zip *)(a->format->data);

	offset = archive_filter_bytes(&a->archive, 0);
	ret = 0;

	/*
	 * We only support uncompressed metadata.
	 */
	if (rsrc->compression != 0) {
		archive_set_error(&a->archive, 22,
		    "Unsupported ZIP compression method (%s)",
		    compression_name(rsrc->compression));
		return (-20);
	}

	/*
	 * The metadata is stored in the "rsrc" entry.  The size of the
	 * metadata is stored in the "size" field of the rsrc entry.
	 *
	 * The size of the metadata is usually small, but we protect
	 * against a huge size by limiting the metadata to 4MB.
	 */
	if (rsrc->uncompressed_size > 4 * 1024 * 1024) {
		archive_set_error(&a->archive, 22,
		    "Mac metadata is too large: %jd > 4M bytes",
		    (intmax_t)rsrc->uncompressed_size);
		return (-20);
	}

	metadata = malloc(rsrc->uncompressed_size);
	if (metadata == NULL) {
		archive_set_error(&a->archive, 12,
		    "Can't allocate memory for Mac metadata");
		return (-30);
	}

	/*
	 * Read the metadata.
	 */
	if (offset < rsrc->local_header_offset)
		__archive_read_consume(a, rsrc->local_header_offset - offset);
	else if (offset != rsrc->local_header_offset)
		__archive_read_seek(a, rsrc->local_header_offset, SEEK_SET);

	hsize = zip_get_local_file_header_size(a, 0);
	__archive_read_consume(a, hsize);

	remaining_bytes = rsrc->compressed_size;
	metadata_bytes = rsrc->uncompressed_size;
	mp = metadata;
	eof = 0;
	while (!eof && remaining_bytes > 0) {
		size_t bytes_used;
		const void *data = __archive_read_ahead(a, 1, &bytes_avail);
		if (data == NULL) {
			archive_set_error(&a->archive, 22,
			    "Truncated ZIP file header");
			ret = -20;
			break;
		}
		if (bytes_avail > remaining_bytes)
			bytes_avail = remaining_bytes;
		if (rsrc->compression == 0) {
			memcpy(mp, data, bytes_avail);
			bytes_used = bytes_avail;
			metadata_bytes -= bytes_avail;
			mp += bytes_avail;
			if (metadata_bytes == 0)
				eof = 1;
		} else
			bytes_used = 0;
		__archive_read_consume(a, bytes_used);
		remaining_bytes -= bytes_used;
	}

	archive_entry_copy_mac_metadata(entry, metadata,
	    rsrc->uncompressed_size - metadata_bytes);

	__archive_read_seek(a, offset, SEEK_SET);
	zip->decompress_init = 0;
	free(metadata);
	return (ret);
}