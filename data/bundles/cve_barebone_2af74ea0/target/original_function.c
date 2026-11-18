static int
vips_source_read_to_memory(VipsSource *source)
{
	GByteArray *byte_array;
	gint64 read_position;
	unsigned char *q;

	VIPS_DEBUG_MSG("vips_source_read_to_memory:\n");

	g_assert(!source->is_pipe);
	g_assert(!source->blob);
	g_assert(!source->header_bytes);
	g_assert(source->length >= 0);

	if (vips_source_rewind(source))
		return -1;

	/* We know the length, so we can size the buffer correctly and read
	 * directly to it.
	 */
	byte_array = g_byte_array_new();
	g_byte_array_set_size(byte_array, source->length);

	read_position = 0;
	q = byte_array->data;
	while (read_position < source->length) {
		gint64 bytes_read;

		bytes_read = vips_source_read(source, q,
			VIPS_MAX(4096, source->length - read_position));
		if (bytes_read == -1) {
			VIPS_FREEF(g_byte_array_unref, byte_array);
			return -1;
		}
		if (bytes_read == 0)
			break;

		read_position += bytes_read;
		q += bytes_read;
	}

	/* Steal the byte_array pointer and turn into a memory source.
	 *
	 * We save byte_array in the header_bytes field to get it freed when
	 * we are freed.
	 */
	source->data = byte_array->data;
	source->is_pipe = FALSE;
	source->header_bytes = byte_array;

	vips_source_minimise(source);

	return 0;
}