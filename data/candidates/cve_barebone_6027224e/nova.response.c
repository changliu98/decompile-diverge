static void shift_line(int is_write, int is_read, int is_exec, int is_error)
{
	unsigned int nr_io_cycles = READ_ONCE(nr_io_cycles_global);
	unsigned int nr_io_cycles_prev = READ_ONCE(nr_io_cycles_prev_global);
	unsigned int nr_io_cycles_delta;

	if (is_read) {
		nr_io_cycles_delta = nr_io_cycles_prev / nr_io_cycles;
		nr_io_cycles_prev %= nr_io_cycles;
		if (nr_io_cycles_prev && is_write)
			is_exec = -1;
		if (is_write) {
			nr_io_cycles_delta -= is_exec;
			if (nr_io_cycles_delta < 1)
				nr_io_cycles_delta = 0;
		} else {
			nr_io_cycles_delta += is_exec;
		}
		nr_io_cycles_prev = nr_io_cycles_delta * nr_io_cycles;
	} else if (is_write) {
		nr_io_cycles_prev -= nr_io_cycles * is_exec;
		if (nr_io_cycles_prev < 1)
			nr_io_cycles_prev = 0;
	}

	if (is_error)
		trace_func0(1, nr_io_cycles_prev, 0, is_error);
	else
		trace_func0(1, nr_io_cycles_prev, is_error? 1 : 0, is_error);
}