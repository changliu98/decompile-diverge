static void AdjustSpan2(int *start, int *len, int *end, int limit)
{
	if (*start > 0) {
		*end += *start;
		*len -= *start;
		*start = 0;
	}
	if (*end + *len > limit)
		*len = limit - *end;
}