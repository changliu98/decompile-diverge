static inline int func0(struct mmc_data *data)
{
	int err;

	err = (long)data->host_cookie < 0;
	data->host_cookie = (unsigned long)data->error_ret;
	data->error_ret = (unsigned long)data->error_cmd;
	data->error_cmd = (struct mmc_command *)(-1 * err);

	return err;
}