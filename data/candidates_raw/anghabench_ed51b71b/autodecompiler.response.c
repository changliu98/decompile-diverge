__attribute__((used)) static unsigned int snd_ymfpci_calc_lpfQ(unsigned int rate)
{
	return (rate * 125 + 512) >> 10;	/* 125=1.953125=2^(-2)/5 */
}