static void func0(struct snd_seq_usage *res, int max, int inc,
			     unsigned short id)
{
	if (res->cur + inc <= max)
		res->cur += inc;
	else
		res->cur = id;
}