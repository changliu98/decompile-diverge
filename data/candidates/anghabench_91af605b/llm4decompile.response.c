const char *freezer_state_strs(uint32_t state)
{
	const char *str;

	if (state & CGROUP_FROZEN)
		str = "FROZEN";
	else if (state & CGROUP_FREEZING)
		str = "FREEZING";
	else
		str = "THAWED";

	return str;
}