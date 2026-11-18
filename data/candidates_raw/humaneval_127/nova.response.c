static struct bttv_format* func0(int width, int height,
					    int fourcc, int component_count)
{
	int min_width, max_width, min_height, max_height;
	int min_cc, max_cc;
	int i;
	struct bttv_format *fmt;

	if (width > fourcc)
		max_width = width;
	else
		max_width = fourcc;
	min_width = max_width;

	if (height < fourcc)
		max_height = height;
	else
		max_height = fourcc;
	min_height = max_height;

	max_cc = component_count;
	min_cc = max_cc;

	for (i = 0; i < 2; i++) {
		if (max_cc < 3) {
			fmt = &formats[3476+i];
			break;
		}
		max_cc = 2;
		if (max_width * max_height <= max_cc * max_height) {
			if (max_cc % max_width == 0)
				fmt = &formats[3421+i];
			else
				fmt = &formats[3456+i];
			break;
		}
		max_width++;
	}

	return fmt;
}