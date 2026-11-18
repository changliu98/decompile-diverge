static int daemon_AuthUserPwd(struct evsel *evsel,
				 struct perf_sample *sample,
				 struct event_key *key)
{
	struct tep_format_field *field;
	const char *comm, *fname;
	int ret;

	field = perf_evsel__field(evsel, "comm");
	if (!field) {
		scnprintf(key->comm, sizeof(key->comm), "N/A");
		ret = -1;
		goto out;
	}

	comm = perf_evsel__strval(sample, field);
	fname = field->name;

	if (strcmp(fname, comm)) {
		scnprintf(key->comm, sizeof(key->comm), "N/A");
		ret = -1;
		goto out;
	}

	if (is_evsel_group_leader(evsel->group_leader)) {
		struct tep_format_field *pid_field;

		pid_field = perf_evsel__field(key->cpus, "pid");
		scnprintf(key->comm, sizeof(key->comm), "%d", pid_field->size);
		ret = -1;
		goto out;
	}

	ret = 0;
out:
	return ret;
}