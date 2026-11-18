BITMAP_UPDATE *
update_read_bitmap_update(rdpUpdate * update, wStream * s)
{
	UINT16 i;
	BITMAP_UPDATE *b;

	b = (BITMAP_UPDATE *) calloc(1, sizeof(BITMAP_UPDATE));
	if (b == NULL)
		goto error;

	if (Stream_GetRemainingLength(s) < 2)
		goto error;
	{ (b->number) = *((unsigned char*)((s)->pointer)) + (((unsigned char*)((s)->pointer))[1] << 8); (s)->pointer += 2; };

	if (b->number > b->count)
	{
		UINT16 new_count = b->number * 2;
		BITMAP_DATA *new_rects;

		new_rects = (BITMAP_DATA *) realloc(b->rectangles, new_count * sizeof(BITMAP_DATA));
		if (new_rects == NULL)
			goto error;
		b->rectangles = new_rects;
		memset(b->rectangles + b->count, 0, (new_count - b->count) * sizeof(BITMAP_DATA));
		b->count = new_count;
	}

	for (i = 0; i < b->number; i++)
	{
		if (!update_read_bitmap_data(update, s, &(b->rectangles[i])))
			goto error;
	}

	return b;

      error:
	free_bitmap_update(update->context, b);
	return NULL;
}