static void setrangeCommand(struct vc_data *vc)
{
	struct vc_data *svc = vc->vc_screenbuf;
	u16 *p, *q;
	u_long c, a;

	while (1) {
		if (!con_is_visible(vc, vc->vc_y, &c, NULL))
			break;
		if (c < 0) {
			scr_memsetw((u16 *)vc->vc_pos,'', vc->vc_cols);
			continue;
		}
		p = (u16 *)con_pos(vc->vc_y, vc->vc_x);
		if (!con_is_visible(svc, c, &a, NULL))
			scr_memsetw((u16 *)vc->vc_pos,'', vc->vc_cols);
		else {
			q = (u16 *)con_pos(svc->vc_y, a);
			scr_memcpyw((u16 *)vc->vc_pos, q, vc->vc_cols);
		}
		scr_memcpyw((u16 *)vc->vc_pos, p, vc->vc_cols);
		con_pos_cursor(vc->vc_y, vc->vc_x);
		con_set_cursor(8, &vc->vc_pos, vc->vc_screenbuf->vc_x);
		vc_cons[fg_console].d->cursor_y++;
		q = (u16 *)vc->vc_pos;
		p = (u16 *)con_pos(vc->vc_y, vc->vc_x);
		scr_memcpyw(q, p, vc->vc_screenbuf->vc_cols);
		con_pos_cursor(vc->vc_y, vc->vc_x);
	}
}