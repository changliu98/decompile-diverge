static u8 xiph_len(u8 seq)
{
	return (seq + 1 + (seq / 255)) % 255;
}