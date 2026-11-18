static int
parse_matrix_header(char *line,
	int *width, int *height, double *scale, double *offset)
{
	double header[4];
	char *p, *q;
	int i;

	/* Stop at newline.
	 */
	if ((p = strchr(line, '\r')) ||
		((p = strchr(line, '\n'))))
		*p = '\0';

	for (i = 0, p = line; (q = vips_break_token(p, " \t")) && i < 4; i++, p = q)
		if (vips_strtod(p, &header[i])) {
			vips_error("matload", _("bad number \"%s\""), p);
			return -1;
		}

	if (i < 4)
		header[3] = 0.0;
	if (i < 3)
		header[2] = 1.0;
	if (i < 2) {
		vips_error("matload", "%s", _("no width / height"));
		return -1;
	}

	if (floor(header[0]) != header[0] ||
		floor(header[1]) != header[1]) {
		vips_error("mask2vips", "%s", _("width / height not int"));
		return -1;
	}

	/* Width / height can be 65536 for a 16-bit LUT, for example.
	 */
	*width = header[0];
	*height = header[1];
	if (*width <= 0 ||
		*width > 100000 ||
		*height <= 0 ||
		*height > 100000) {
		vips_error("mask2vips", "%s", _("width / height out of range"));
		return -1;
	}
	if (header[2] == 0.0) {
		vips_error("mask2vips", "%s", _("zero scale"));
		return -1;
	}

	*scale = header[2];
	*offset = header[3];

	return 0;
}