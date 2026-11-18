static inline u8 and_peep2_q(u8 agc, u8 *p_tx_pwr_by_rate)
{
	*p_tx_pwr_by_rate = agc & 0xfe;
	return agc;
}