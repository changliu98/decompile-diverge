__attribute__((used)) static unsigned int get_high_speed_hz(unsigned int rate)
{
	return (rate * 125 + 512) >> 10;	/* 125=1.953125=2^(-2)/5 */
}