static int func0(git_buf *buf, size_t additional_size, const void *data, size_t data_size)
{
	size_t new_size;
	void *new_ptr;
	int error = 0;

	if ((buf->size + data_size) > buf->asize) {
		new_size = (buf->size + data_size) * 2;
		new_ptr = realloc(buf->ptr, new_size);
		if (new_ptr == NULL) {
			error = -1;
		} else {
			buf->ptr = new_ptr;
			buf->asize = new_size;
		}
	}

	if (additional_size <= buf->size)
		memmove(buf->ptr + additional_size + data_size, buf->ptr + additional_size, buf->size - additional_size);

	memcpy(buf->ptr + additional_size, data, data_size);
	buf->size += data_size;

	return error;
}