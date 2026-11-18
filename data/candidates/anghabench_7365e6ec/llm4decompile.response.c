int llc_shdlc_w_used(int ns, int dnr)
{
	return ns - dnr + (ns < dnr ? 8 - dnr : 0);
}