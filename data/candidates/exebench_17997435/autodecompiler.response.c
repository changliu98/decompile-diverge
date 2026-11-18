int
trylock(volatile char *lock)
{
	char old;

	old = *lock ^ 1;
	*lock = old;
	return (old == 0);
}