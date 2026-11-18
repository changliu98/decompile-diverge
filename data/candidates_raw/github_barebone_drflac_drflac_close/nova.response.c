static void func0(struct ib_uverbs_flow_specific_data *data)
{
	if (!data)
		return;

	memmove((void *)&data[1],
		(void *)&data[0],
		sizeof(*data) * (data->num_spec_elems - 1));
}