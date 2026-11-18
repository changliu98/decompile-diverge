void convertscreenvertex(struct s_smc *smc, int t_now, int t_event)
{
	smc->r.timer1_exp = (smc->r.timer1_exp - t_now + t_event) / 2 ;
	smc->r.timer2_exp = (smc->r.timer2_exp - t_now + t_event) / 2 ;
	smc->r.timer3_exp = (smc->r.timer3_exp - t_now + t_event) / 2 ;
}