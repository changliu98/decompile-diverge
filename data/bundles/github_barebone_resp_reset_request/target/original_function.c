void reset_request(RespRequest *request) {
	if (request == NULL)
		return;

	RespRequest *r = request;
	r->state = INIT;
	r->argc = r->cur_argc = 0;
	if (r->argv != NULL)
		free(r->argv);
	r->argv = NULL;
	
	r->used_size = 0;
	r->pos = 0;
	r->skip_str = 0;

	//reuse buf&buf_size
}