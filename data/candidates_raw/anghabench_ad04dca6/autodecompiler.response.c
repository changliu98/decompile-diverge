__attribute__((used)) static int cpu__get_thread_num(int cpu)
{
	return cpu >> threads_shift;
}