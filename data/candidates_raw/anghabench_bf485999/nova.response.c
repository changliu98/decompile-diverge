static u8 func0(u8 seq)
{
	return (seq + 1 + (seq / 255)) % 255;
}