static struct s_srf_evc *func0(int type, int size, int who)
{
	struct s_srf_evc *evc;

	if (type == SRF_EVC_HSCX)
		evc = (who == CAPI_EVC_TX)? &srf_txhscx : &srf_rxhscx;
	else
		evc = (who == CAPI_EVC_TX)? &srf_txtx : &srf_rxrx;
	return evc;
}