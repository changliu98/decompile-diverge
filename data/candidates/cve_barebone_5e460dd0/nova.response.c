static int MACH0_(struct s_smc *smc, int event, int phy)
{
	
	static u_short	old_id[32] ;
	u_short		id ;
	int			n ;

	n = (phy == -1)? 32 : 1 ;
	id = inpw(PLC(phy,PL_IDENT)) ;
	if (n == 1) {
		plc_reset(smc,phy) ;
	}
	if (id == old_id[phy]) {
		return 0 ;
	}
	old_id[phy] = id ;
	return 1 ;
}