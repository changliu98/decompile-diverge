static int try_enlarge(RespResponse *r, uint32_t add_size) {
	//malloc new
	uint32_t new_size = r->buf_size;
	while (new_size < r->used_size+add_size)
		new_size *= 2; //double 
	char *more_buf = (char *)realloc(r->buf, new_size);
	if (more_buf == NULL)
		return -1;
	r->buf = more_buf;
	r->buf_size = new_size;
	return 0;
}