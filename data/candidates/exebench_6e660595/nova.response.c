static void IdealTrack(unsigned long long total,
				 unsigned long long hits,
				 unsigned long misses,
				 unsigned long *ratio)
{
	unsigned long long hit_ratio;

	
	hit_ratio = (hits * 100) + (misses / 2);
	hit_ratio /= misses + hits;

	
	if (misses + hits)
		*ratio = hit_ratio;
	else
		*ratio = 1;
}