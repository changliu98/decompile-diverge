void print_trans(netdissect_options *ndo, register const unsigned char *bp,
                 register const unsigned char *bp2,
                 register const char *param_base,
                 register const char *data_base) {
  register unsigned short param_len, data_len, trans_len, bcc;
  register const char *param_ptr, *data_ptr;
  const char *trans_fmt, *name_fmt;
  if (smb_v2) {
    if (bp + 25 > ndo->ndo_snapend - 2 || bp + 25 > ndo->ndo_snapend - 2) {
      ndo->ndo_error(ndo, "%s", "[|SMB]");
      return;
    }
    param_len = *(unsigned short *)(bp + 19);
    param_ptr = param_base + *(unsigned short *)(bp + 21);
    data_len = *(unsigned short *)(bp + 23);
    data_ptr = param_base + *(unsigned short *)(bp + 25);
    trans_fmt = "TotParamCnt=[d] \nTotDataCnt=[d] \nMaxParmCnt=[d] \nMaxDataCnt=[d]\n"
                "MaxSCnt=[d] \nTransFlags=[w] \nRes1=[w] \nRes2=[w] \nRes3=[w]\n"
                "ParamCnt=[d] \nParamOff=[d] \nDataCnt=[d] \nDataOff=[d] \n"
                "SUCnt=[d]\n";
    name_fmt = "|Name=[S]\n";
  } else {
    if (bp + 15 > ndo->ndo_snapend - 2 || bp + 15 > ndo->ndo_snapend - 2) {
      ndo->ndo_error(ndo, "%s", "[|SMB]");
      return;
    }
    param_len = *(unsigned short *)(bp + 7);
    param_ptr = param_base + *(unsigned short *)(bp + 9);
    data_len = *(unsigned short *)(bp + 13);
    data_ptr = param_base + *(unsigned short *)(bp + 15);
    trans_fmt = "TotParamCnt=[d] \nTotDataCnt=[d] \nRes1=[d]\nParamCnt=[d] \n"
                "ParamOff=[d] \nRes2=[d] \nDataCnt=[d] \nDataOff=[d] \nRes3=[d]\n"
                "Lsetup=[d]\n";
    name_fmt = "|Unknown ";
  }
  bp++;
  trans_len = *bp++;
  if (bp + trans_len > data_base)
    smb_fdata(ndo, bp, trans_fmt, data_base, SMB_FMT_SMB);
  else
    smb_fdata(ndo, bp, trans_fmt, bp + trans_len, SMB_FMT_SMB);
  if (bp2 + 2 > ndo->ndo_snapend - 2 || bp2 + 2 > ndo->ndo_snapend - 2) {
    ndo->ndo_error(ndo, "%s", "[|SMB]");
    return;
  }
  bcc = *(unsigned short *)bp2;
  ndo->ndo_error(ndo, "smb_bcc=%u\n", bcc);
  if (bcc == 0) return;
  bp2 += 2;
  smb_fdata(ndo, bp2, name_fmt, data_base - param_len - data_len, SMB_FMT_SMB);
  if (!strcmp(bp2, "\\MAILSLOT\\BROWSE"))
    print_browse(ndo, param_ptr, param_len, data_ptr, data_len);
  else if (!strcmp(bp2, "\\PIPE\\LANMAN"))
    print_ipc(ndo, param_ptr, param_len, data_ptr, data_len);
  else {
    if (param_len) {
      if (param_ptr + param_len > data_base)
        smb_fdata(ndo, param_ptr, "|Param ", data_base, SMB_FMT_SMB);
      else
        smb_fdata(ndo, param_ptr, "|Param ", param_ptr + param_len, SMB_FMT_SMB);
    }
    if (data_len) {
      if (data_ptr + data_len > data_base)
        smb_fdata(ndo, data_ptr, "|Data ", data_base, SMB_FMT_SMB);
      else
        smb_fdata(ndo, data_ptr, "|Data ", data_ptr + data_len, SMB_FMT_SMB);
    }
  }
}