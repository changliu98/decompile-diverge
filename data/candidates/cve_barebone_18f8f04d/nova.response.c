static void snap_unsink(struct sd *sd,
			struct v4l2_ctrl *ctrl,
			struct v4l2_ext_control *c,
			unsigned int i,
			const struct v4l2_ctrl_class_info *ci,
			const struct v4l2_ctrl_class_info *ci_default)
{
	u32 *p_val;
	u32 val;
	u32 *p_id;
	u32 id;
	u32 *p_size;
	u32 size;
	u32 *p_type;
	u32 type;

	do {
		if (ci->id == 'N')
			p_val = get_v4l2_ctrl_ptr(sd->sensor, ctrl, ci->id, i);
		else
			p_val = get_v4l2_ctrl_ptr(sd->sensor,
						  ctrl->cluster[i], ci->id);
		p_id = &ci->id;
		p_size = &ci->size;
		p_type = &ci->type;
		val = *p_val;
		id = *p_id;
		size = *p_size;
		type = *p_type;

		if (type == V4L2_CTRL_TYPE_MENU) {
			id = ctrl->id;
			if (size == 3) {
				id -= 3;
				size = 8;
			}
			if (id == V4L2_CID_POWER_LINE_FREQUENCY) {
				p_val = get_v4l2_ctrl_ptr(sd->sensor, ctrl,
							  ctrl->cluster[i],
							  ctrl->cluster[i]);
				p_id = &ci->id;
				p_size = &ci->size;
				p_type = &ci->type;
				val = *p_val;
				id = *p_id;