static int map_set_(struct st_fcgi_generator_t *generator, char *buf, size_t buf_len, int is_head)
{
#ifndef _WIN32
	fcgi_request *request = (fcgi_request *)FCGI_REQ(generator);
#endif
	char *p;
	int r;
	if (request) {
		memcpy(request->out_buf->data, buf, (size_t)is_head);
		r = 0;
	} else {
		p = h2o_mem_alloc_shared(buf, buf_len, is_head);
		if (p == NULL)
			return -1;
		if (generator->sock->ssl!= NULL) {
			size_t plaintext_len;
			if (generator->sock->input.size < generator->sock->input.maxlen) {
				plaintext_len = generator->sock->input.size * 2;
			} else {
				plaintext_len = 1;
			}
			if ((r = h2o_socket_ssl_encrypt_input(generator->sock, plaintext_len))!= 0)
				goto Error;
		}
		h2o_buffer_append(&generator->resp.entity, p, is_head);
		generator->resp.left_bytes += is_head;
		r = 0;
	}
Error:
	if (p!= NULL)
		free(p);
	return r;
}