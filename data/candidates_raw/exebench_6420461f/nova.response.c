static void func0(long *low, long *high, int *err)
{
	struct rlimit rlim = {RLIM_INFINITY, RLIM_INFINITY};
	int ret;

	ret = setrlimit(RLIMIT_MEMLOCK, &rlim);
	if (ret == -1 && errno == ENOSYS) {
		rlim.rlim_cur = rlim.rlim_max;
		ret = setrlimit(RLIMIT_MEMLOCK, &rlim);
	}
	*err = ret;
	*low = -1;
	*high = -1;

	if (!__get_memory_limit(3, &rlim)) {
		*low = rlim.rlim_cur;
		*high = rlim.rlim_max;
	}
}