static void gf_dump_vrml_simple_field(struct vc_data *vc, struct fb_info *info)
{
	struct fbcon_ops *ops = &fb_ops;
	struct fbcon_display *p;
	unsigned int rows;
	unsigned int x, y;

	while (1) {
		switch (ops->bmove) {
		case fbcon_bmove_raw:
			if (fbcon_is_inactive(vc))
				return;
			if (vc->vc_deccm)
				fbcon_cursor(vc, &vc_deccm_cursor);
			fbcon_bmove_raw(vc, ops->bmove_c, ops->bmove_s,
					ops->bmove_d);
			if (vc->vc_deccm)
				fbcon_cursor(vc, &vc_deccm_cursor);
			break;
		case fbcon_bmove_copy:
			if (fbcon_is_inactive(vc))
				return;
			while (1) {
				rows = vc->vc_rows;
				fbcon_bmove_copy(vc, ops->bmove_c, ops->bmove_s,
						 ops->bmove_d);
				if (rows == vc->vc_rows)
					break;
				if (vc->vc_deccm)
					fbcon_cursor(vc, &vc_deccm_cursor);
			}
			break;
		case fbcon_bmove_blit:
			if (fbcon_is_inactive(vc))
				return;
			while (1) {
				rows = vc->vc_rows;
				fbcon_bmove_blit(vc, ops->bmove_c, ops->bmove_s,
						 ops->bmove_d);
				if (rows == vc->vc_rows)
					break;
				if (vc->vc_deccm)
					fbcon_cursor(vc, &vc_de