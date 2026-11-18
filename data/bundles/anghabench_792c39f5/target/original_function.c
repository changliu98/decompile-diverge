bool check_need_swap(int file_endian)
{
	const int data = 1;
	u8 *check = (u8 *)&data;
	int host_endian;

	if (check[0] == 1)
		host_endian = ELFDATA2LSB;
	else
		host_endian = ELFDATA2MSB;

	return host_endian != file_endian;
}