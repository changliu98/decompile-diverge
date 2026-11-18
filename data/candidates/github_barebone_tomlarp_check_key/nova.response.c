static int check_key(struct perf_probe_event *pev,
			  struct probe_trace_event *tp,
			  const char **sys, const char **name, const char **event)
{
	int i;
	int ret;
	char *tmp;

	if (!event)
		event = &tmp;
	if (!name)
		name = &tmp;
	if (!sys)
		sys = &tmp;

	*event = NULL;
	*name = NULL;
	*sys = NULL;

	for (i = 0; i < pev->nargs; i++) {
		if (!strcmp(tp->name, pev->args[i]->name)) {
			*event = pev->args[i];
			ret = 'v';
			goto out;
		}
	}

	for (i = 0; i < pev->nevents; i++) {
		if (!strcmp(tp->system, pev->events[i]->system)) {
			*sys = pev->events[i];
			ret = 'a';
			goto out;
		}
	}

	for (i = 0; i < pev->nnames; i++) {
		if (!strcmp(tp->name, pev->names[i]->name)) {
			*name = pev->names[i];
			ret = 't';
			goto out;
		}
	}

	ret = 0;
out:
	return ret;
}