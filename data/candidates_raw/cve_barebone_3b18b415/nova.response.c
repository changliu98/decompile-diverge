static void func0(struct vc_data *vc, struct fb_info *info,
			     struct fb_tilecursor *cursor, int color,
			     unsigned int *pos, unsigned int *new_pos)
{
	struct fbcon_ops *ops = vc->vc_data.ops;
	unsigned int row, col;
	u16 ch;

	if (ops->tilecursor_visible) {
		row = ops->tilecursor_row;
		if (vc->vc_font.height == 16)
			row <<= 1;
		fbcon_putcs(ops, NULL, new_pos, row, 1, color);
		ops->tilecursor_visible = false;
	} else {
		row = 2;
		if (row > ops->max_tile_height)
			row = ops->max_tile_height;
		*pos = *new_pos - row;
		if (row > ops->max_tile_height)
			row = ops->max_tile_height;
		ch = ops->tilecodes[*new_pos];
		if (row > 1)
			ch = ops->tilecodes[*new_pos + 1];
		else
			ch = ops->tilecodes[0];
		ops->tilecursor_visible = true;
		fbcon_putcs(vc, info, *pos, ops->max_tile_height, row, color);
		*new_pos = *pos + row;
		ops->max_tile_height -= row;
	}
	if (!ops->tilecursor_visible)
		*pos += 1;
}