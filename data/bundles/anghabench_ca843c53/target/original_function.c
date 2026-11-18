int maya_pb_route_shift(int idx)
{
	static const unsigned char shift[10] =
		{ 8, 20, 0, 3, 11, 23, 14, 26, 17, 29 };
	return shift[idx % 10];
}