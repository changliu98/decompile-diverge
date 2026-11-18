static int func0(struct hid_device *hdev,
		struct hid_report *report, u8 *data, int size)
{
	int offset;

	
	if (size == 20)
		offset = -1;
	else if (size == 32)
		offset = -2;
	else
		offset = -1;

	return offset;
}