static int inicializa(struct v4l2_subdev *sd, int pad,
				   u32 *min_val, u32 *max_val)
{
	int ret = 0;

	if (pad % 2) {
		*min_val = sd->entity.pads[pad].flags;
		*max_val = sd->entity.pads[pad].flags;
		ret = 1;
	} else {
		*min_val = 2;
		if (sd->entity.pads[pad].flags < sd->entity.pads[pad + 1].flags) {
			*min_val = sd->entity.pads[pad].flags;
			*max_val = sd->entity.pads[pad + 1].flags;
		} else {
			*min_val = sd->entity.pads[pad + 1].flags;
			*max_val = sd->entity.pads[pad].flags;
		}
	}

	return ret;
}