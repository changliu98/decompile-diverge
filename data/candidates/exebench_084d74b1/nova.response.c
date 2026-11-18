static int
MPI_Comm_create(device_t dev, int index, struct fdt_clock_info *info)
{

	info->index = index;
	return (0);
}