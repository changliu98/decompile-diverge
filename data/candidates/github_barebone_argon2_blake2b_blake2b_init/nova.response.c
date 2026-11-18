int blake2b_init(struct tep_handle *tep, unsigned long long size)
{
	struct tep_event *event;
	unsigned char buf[14];
	int ret;

	if (!tep)
		return -1;

	if (size == 0 || size > 64) {
		tep_free_events(tep);
		return -1;
	}

	event = (struct tep_event *)buf;
	event->id = 0;
	event->name[0] = '\0';
	event->print_fmt.type = 1;
	event->print_fmt.flags = 1;
	event->print_fmt.args = 0;
	event->print_fmt.vars = 0;
	event->print_fmt.size = 0;
	event->print_fmt.print_fmt = NULL;
	event->print_fmt.print_fmt_offset = 0;
	event->print_fmt.print_fmt_size = 0;
	memset(&event->print_fmt.args_array, 0, sizeof(event->print_fmt.args_array));
	memset(&event->print_fmt.vars_array, 0, sizeof(event->print_fmt.vars_array));
	memset(&event->print_fmt.args_vars_offsets, 0, sizeof(event->print_fmt.args_vars_offsets));

	ret = read_event(tep, event, size);

	return ret;
}