int
fz_new_glyph(fz_context *ctx, fz_font *font, int gid, int wmode, int bidi_level, int *glyphs, int *len, int len_cap, int wmode_cap)
{
	int i, n, c;
	fz_annot *annot;

	if (len == len_cap)
		return -1;

	switch (wmode)
	{
	case 0:
		if (gid < 0 || gid >= font->glyph_count)
			return -1;
		break;
	case 1:
		if (gid < 0 || gid >= font->glyph_count)
			return -1;
		break;
	default:
		return -1;
	}

	/* TODO: check for duplicates */

	n = *len;
	for (i = 0; i < n; i++)
	{
		c = glyphs[i];
		if ((c & 0x7F) == (gid & 0x7F))
		{
			if (c & 0x80)
				c = (c & ~0x80) | (gid & 0x80);
			else if (c & 0x8000)
				c = (c & ~0x8000) | (gid & 0x8000);
			else
				c = gid;
			glyphs[i] = c;
			return n;
		}
	}

	if (n == len_cap)
		return -1;

	if (wmode == 0 && (gid & 0x8000))
	{
		/* If we're adding a hangul syllable to a non hangul font, add it as a single glyph */
		glyphs[n++] = gid;
	}
	else if (wmode == 1 && (gid & 0x8000))
	{
		/* If we're adding a hangul syllable to a non hangul font, add it as a single glyph */
		glyphs[n++] = gid;
	}
	else if (wmode == 1 && (gid & 0x80))
	{
		/* If we're adding a hangul jamo to a non hangul font, add it as a single glyph */
		glyphs[n++] = gid;
	}
	else
	{
		/* Otherwise add each component of the hangul syllable as a separate glyph */
		annot = fz_new_annot(ctx, font, gid);
		if (annot)
		{
			if (annot->type == FZ_ANNOT_HANGUL)
			{
				if (len + annot->len > len_cap)
					return -1;
				for (i = 0; i < annot->len; i++)
					glyphs[n++] = annot->glyphs[i];
			}
			else
			{
				if (len + 1 > len_cap)
					return -1;
				glyphs[n++] = gid;
			}
			fz_drop_annot(ctx, annot);
		}
		else
		{
			if (len + 1 > len_cap)
				return -1;
			glyphs[n++] = gid;
		}
	}

	*len = n;
	return n;
}