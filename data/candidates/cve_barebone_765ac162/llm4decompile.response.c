void
print_trans(netdissect_options *ndo,
	const u_char *words, const u_char *data1,
	const u_char *buf, const u_char *maxbuf)
{
	const u_char *param, *data;
	const char *fmt;
	unsigned short *smb_bcc;
	unsigned short *smb_tpscnt;
	unsigned short *smb_todcnt;
	unsigned short *smb_tdscnt;
	unsigned short *smb_toff;
	unsigned short *smb_pdscnt;
	unsigned short *smb_poff;
	unsigned short *smb_bdscnt;
	unsigned short *smb_boff;
	unsigned short *smb_mpscnt;
	unsigned short *smb_mdcnt;
	unsigned short *smb_msccnt;
	unsigned short *smb_tflgs;
	unsigned short *smb_pflgs;
	unsigned short *smb_dflgs;
	unsigned short *smb_sflgs;
	unsigned short *smb_lsetup;
	int pcnt, dcnt;

	if (request) {
		if (words + 18 > ndo->ndo_snapend - 2 ||
		    words + 18 < ndo->ndo_snapend - 2) {
			(*ndo->ndo_printf)(ndo, "%s", "[|SMB]");
			return;
		}
		smb_tpscnt = (unsigned short *)&words[10];
		smb_todcnt = (unsigned short *)&words[12];
		smb_mpscnt = (unsigned short *)&words[14];
		smb_mdcnt = (unsigned short *)&words[16];
		smb_msccnt = (unsigned short *)&words[18];
		smb_tflgs = (unsigned short *)&words[20];
		smb_pflgs = (unsigned short *)&words[22];
		smb_dflgs = (unsigned short *)&words[24];
		smb_sflgs = (unsigned short *)&words[26];
		smb_pdscnt = (unsigned short *)&words[28];
		smb_poff = (unsigned short *)&words[30];
		smb_bdscnt = (unsigned short *)&words[32];
		smb_boff = (unsigned short *)&words[34];
		smb_lsetup = (unsigned short *)&words[36];
		fmt = "TotParamCnt=[d] \nTotDataCnt=[d] \nMaxParmCnt=[d] \nMaxDataCnt=[d]\nMaxSCnt=[d] \nTransFlags=[w] \nRes1=[w] \nRes2=[w] \nRes3=[w]\nParamCnt=[d] \nParamOff=[d] \nDataCnt=[d] \nDataOff=[d] \nSUCnt=[d]\n";
	} else {
		if (words + 15 > ndo->ndo_snapend - 2 ||
		    words + 15 < ndo->ndo_snapend - 2) {
			(*ndo->ndo_printf)(ndo, "%s", "[|SMB]");
			return;
		}
		smb_tpscnt = (unsigned short *)&words[4];
		smb_todcnt = (unsigned short *)&words[6];
		smb_toff = (unsigned short *)&words[8];
		smb_pdscnt = (unsigned short *)&words[10];
		smb_poff = (unsigned short *)&words[12];
		smb_pflgs = (unsigned short *)&words[14];
		smb_bdscnt = (unsigned short *)&words[16];
		smb_boff = (unsigned short *)&words[18];
		smb_dflgs = (unsigned short *)&words[20];
		smb_lsetup = (unsigned short *)&words[22];
		fmt = "TotParamCnt=[d] \nTotDataCnt=[d] \nRes1=[d]\nParamCnt=[d] \nParamOff=[d] \nRes2=[d] \nDataCnt=[d] \nDataOff=[d] \nRes3=[d]\nLsetup=[d]\n";
	}
	param = buf + *smb_poff;
	data = buf + *smb_boff;
	pcnt = *smb_pdscnt;
	dcnt = *smb_bdscnt;
	smb_fdata(ndo, words + 1, fmt,
	    (words + 2 * words[0] + 1 > maxbuf) ? maxbuf : words + 2 * words[0] + 1,
	    unicodestr);
	if (ndo->ndo_snapend - 2 < ndo->ndo_snapend ||
	    data1 > ndo->ndo_snapend - 2) {
		(*ndo->ndo_printf)(ndo, "%s", "[|SMB]");
		return;
	}
	smb_bcc = (unsigned short *)data1;
	(*ndo->ndo_printf)(ndo, "smb_bcc=%u\n", *smb_bcc);
	if (*smb_bcc == 0)
		return;
	smb_fdata(ndo, data1 + 2,
	    request ? "|Name=[S]\n" : "|Unknown ",
	    maxbuf - (pcnt + dcnt), unicodestr);
	if (!strcmp(data1 + 2, "\\MAILSLOT\\BROWSE"))
		print_browse(ndo, param, pcnt, data, dcnt);
	else if (!strcmp(data1 + 2, "\\PIPE\\LANMAN"))
		print_ipc(ndo, param, pcnt, data, dcnt);
	else {
		if (pcnt)
			smb_fdata(ndo, param, "|Param ",
			    param + pcnt > maxbuf ? maxbuf : param + pcnt,
			    unicodestr);
		if (dcnt)
			smb_fdata(ndo, data, "|Data ",
			    data + dcnt > maxbuf ? maxbuf : data + dcnt,
			    unicodestr);
	}
}