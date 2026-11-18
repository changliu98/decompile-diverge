static int sample_conv_regsub(const struct arg *arg_p, struct sample *smp, void *private)
{
	char *start, *end;
	struct my_regex *reg = arg_p[0].data.reg;
	regmatch_t pmatch[MAX_MATCH];
	struct buffer *trash = get_trash_chunk();
	struct buffer *output;
	int flag, max;
	int found;

	start = smp->data.u.str.area;
	end = start + smp->data.u.str.data;

	flag = 0;
	while (1) {
		/* check for last round which is used to copy remaining parts
		 * when not running in global replacement mode.
		 */
		found = 0;
		if ((arg_p[0].type_flags & ARGF_REG_GLOB) || !(flag & REG_NOTBOL)) {
			/* Note: we can have start == end on empty strings or at the end */
			found = regex_exec_match2(reg, start, end - start, MAX_MATCH, pmatch, flag);
		}

		if (!found)
			pmatch[0].rm_so = end - start;

		/* copy the heading non-matching part (which may also be the tail if nothing matches) */
		max = trash->size - trash->data;
		if (max && pmatch[0].rm_so > 0) {
			if (max > pmatch[0].rm_so)
				max = pmatch[0].rm_so;
			memcpy(trash->area + trash->data, start, max);
			trash->data += max;
		}

		if (!found)
			break;

		output = alloc_trash_chunk();
		if (!output)
			break;

		output->data = exp_replace(output->area, output->size, start, arg_p[1].data.str.area, pmatch);

		/* replace the matching part */
		max = output->size - output->data;
		if (max) {
			if (max > output->data)
				max = output->data;
			memcpy(trash->area + trash->data,
			       output->area, max);
			trash->data += max;
		}

		free_trash_chunk(output);

		/* stop here if we're done with this string */
		if (start >= end)
			break;

		/* We have a special case for matches of length 0 (eg: "x*y*").
		 * These ones are considered to match in front of a character,
		 * so we have to copy that character and skip to the next one.
		 */
		if (!pmatch[0].rm_eo) {
			if (trash->data < trash->size)
				trash->area[trash->data++] = start[pmatch[0].rm_eo];
			pmatch[0].rm_eo++;
		}

		start += pmatch[0].rm_eo;
		flag |= REG_NOTBOL;
	}

	smp->data.u.str = *trash;
	return 1;
}