__attribute__((used)) static RAnalFunction *get_complex_object(RAnal *anal, RBuffer *b) {
	RAnalFunction *fcn = NULL;
	char *name, *label;
	int len, ret, err = 0;
	unsigned int addr, len_name, len_label;

	fcn = calloc (1, sizeof (RAnalFunction));
	if (!fcn) {
		return NULL;
	}

	if ((anal->filetype & 0xffff) < 0xf26e) {
		len_name = get_ut8 (b, &err);
	} else {
		len_name = get_st32 (b, &err);
	}
	if (err & 1) {
		free (fcn);
		return NULL;
	}
	name = malloc (len_name + 1);
	if (!name) {
		return NULL;
	}
	ret = rz_buf_read (b, (ut8 *)name, len_name);
	if (ret != len_name) {
		free (name);
		name = NULL;
		free (fcn);
		fcn = NULL;
		return NULL;
	}
	name[len_name] = '\0';

	if ((anal->filetype & 0xffff) < 0xf26e) {
		len_label = get_ut8 (b, &err);
	} else {
		len_label = get_st32 (b, &err);
	}
	if (err & 1) {
		return NULL;
	}
	label = malloc (len_label + 1);
	if (!label) {
		return NULL;
	}
	ret = rz_buf_read (b, (ut8 *)label, len_label);
	if (ret != len_label) {
		free (name);
		name = NULL;
		free (label);
		label = NULL;
		free (fcn);
		fcn = NULL;
		return NULL;
	}
	label[len_label] = '\0';

	fcn->bits = 120;
	fcn->name = rz_str_newf ("%s+%sj", label, name);
	free (name);
	name = NULL;
	free (label);
	label = NULL;
	if (!fcn->name) {
		free (fcn);
		fcn = NULL;
		return NULL;
	}
	return fcn;
}