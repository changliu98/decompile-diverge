__attribute__((used)) static int s390_cpumsf_reached_trailer(struct perf_event *event,
				      unsigned long flags)
{
	unsigned long payload = S390_CPUMSF_PAGESZ - sizeof(struct hws_trailer);
	int ret;

	/*
	 * Check for valid event code.
	 * If the event code does not exist in the table, we will get an
	 * error from the kernel. This is intended to catch typos.
	 */
	if (event->attr.type != PERF_TYPE_RAW)
		return -EINVAL;

	/*
	 * Check if the event is suitable for the counter.
	 * The counter can only count events that have a single record.
	 * Therefore, we do not allow any event that might produce multiple
	 * records.
	 */
	if (payload < event->attr.size)
		ret = 0;
	else
		ret = 1;

	return ret;
}