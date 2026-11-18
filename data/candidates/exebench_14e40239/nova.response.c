static int RGB8toRGB32(struct perf_event_attr *attr, int group_fd,
			    int cpu, int thread, int exclude_kernel,
			    int exclude_user, int precise_ip,
			    struct perf_event_open_attr *open_attr)
{
	(void) attr;
	(void) group_fd;
	(void) cpu;
	(void) thread;
	(void) exclude_kernel;
	(void) exclude_user;
	(void) precise_ip;
	(void) open_attr;
	return -1;
}