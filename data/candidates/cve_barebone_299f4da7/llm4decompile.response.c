void
handle_mlppp(netdissect_options *ndo,
             register const u_char *p, u_int length)
{
	u_int seq;

	if (!ndo->ndo_eflag)
		(*ndo->ndo_printf)(ndo, "MLPPP, ");
	seq = EXTRACT_16BITS(p) & 0x0fff;
	(*ndo->ndo_printf)(ndo, "seq 0x%03x, Flags [%s], length %u",
	    seq, bittok2str(ppp_ml_flag_values, "none", *(p + 0)), length);
}