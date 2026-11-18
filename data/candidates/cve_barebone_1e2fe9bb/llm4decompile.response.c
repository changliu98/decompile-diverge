void
beep_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	if (l_strnstart("MSG", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP MSG");
	else if (l_strnstart("RPY ", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP RPY");
	else if (l_strnstart("ERR ", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP ERR");
	else if (l_strnstart("ANS ", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP ANS");
	else if (l_strnstart("NUL ", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP NUL");
	else if (l_strnstart("SEQ ", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP SEQ");
	else if (l_strnstart("END", 4, bp, length))
		ndo->ndo_printf(ndo, " BEEP END");
	else
		ndo->ndo_printf(ndo, " BEEP (payload or undecoded)");
}