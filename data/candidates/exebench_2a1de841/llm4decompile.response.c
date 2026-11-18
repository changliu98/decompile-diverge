double linsched_rand(unsigned int *state)
{
 *state = (*state * 16807) % 2147483647;
 return (double) *state / 2147483647.0;
}