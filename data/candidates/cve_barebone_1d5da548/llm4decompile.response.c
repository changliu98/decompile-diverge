pyc_object *get_complex_object(RzBinPycObj *pyc, RzBuffer *buffer) {
	int real_len, imag_len;
	char *real_str, *imag_str;
	pyc_object *obj = NULL;
	int rlen, ilen;
	st32 rval, ival;
	ut8 rvalb, ivalb;
	int error = 0;

	if (!(obj = calloc (1, sizeof (pyc_object)))) {
		return NULL;
	}

	if ((pyc->magic_int & 0xffff) >= 0xf26e) {
		rval = get_st32 (buffer, &error);
		if (error & 1) {
			free (obj);
			return NULL;
		}
		real_len = rval;
	} else {
		rvalb = get_ut8 (buffer, &error);
		if (error & 1) {
			free (obj);
			return NULL;
		}
		real_len = rvalb;
	}

	if (!(real_str = malloc (real_len + 1))) {
		return NULL;
	}

	rlen = rz_buf_read (buffer, (ut8 *)real_str, real_len);
	if (rlen != real_len) {
		free (real_str);
		free (obj);
		return NULL;
	}
	real_str[real_len] = '\0';

	if ((pyc->magic_int & 0xffff) >= 0xf26e) {
		ival = get_st32 (buffer, &error);
		if (error & 1) {
			return NULL;
		}
		imag_len = ival;
	} else {
		ivalb = get_ut8 (buffer, &error);
		if (error & 1) {
			return NULL;
		}
		imag_len = ivalb;
	}

	if (!(imag_str = malloc (imag_len + 1))) {
		return NULL;
	}

	ilen = rz_buf_read (buffer, (ut8 *)imag_str, imag_len);
	if (ilen != imag_len) {
		free (real_str);
		free (imag_str);
		free (obj);
		return NULL;
	}
	imag_str[imag_len] = '\0';

	obj->type = TYPE_COMPLEX;
	obj->data = rz_str_newf ("%s+%sj", real_str, imag_str);
	free (real_str);
	free (imag_str);
	if (!obj->data) {
		free (obj);
		return NULL;
	}
	return obj;
}