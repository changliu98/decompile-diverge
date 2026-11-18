nsgif_error nsgif_frame_decode(
		nsgif_t *gif,
		uint32_t frame,
		nsgif_bitmap_t **bitmap)
{
	uint32_t start_frame;
	nsgif_error ret = NSGIF_OK;

	if (frame >= gif->info.frame_count) {
		return NSGIF_ERR_BAD_FRAME;
	}

	if (gif->decoded_frame == frame) {
		*bitmap = gif->frame_image;
		return NSGIF_OK;

	} else if (gif->decoded_frame >= frame ||
	           gif->decoded_frame == NSGIF_FRAME_INVALID) {
		/* Can skip to first frame or restart. */
		start_frame = 0;
	} else {
		start_frame = nsgif__frame_next(
				gif, false, gif->decoded_frame);
	}

	for (uint32_t f = start_frame; f <= frame; f++) {
		ret = nsgif__process_frame(gif, f, true);
		if (ret != NSGIF_OK) {
			return ret;
		}
	}

	*bitmap = gif->frame_image;
	return ret;
}