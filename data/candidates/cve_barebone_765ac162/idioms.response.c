void print_trans(struct netdissect_options *ndo, struct smbhdr *hdr, struct smbparam *param, struct smbdata *data, unsigned char *maxbuf)
{
  int paramlen;
  int datalen;
  unsigned char *paramstart;
  unsigned char *datastart;
  char *paramstr;
  char *datastr;
  unsigned int bcc;
  if (request == 0) {
    if (hdr->totparamlen + 2 > ndo->ndo_snapend - 2 ||
        hdr->paramend + 2 > ndo->ndo_snapend - 2)
      goto trunc;
    paramlen = hdr->totparamlen;
    paramstart = (unsigned char *)hdr->paramstart;
    datalen = hdr->totdatalen;
    datastart = (unsigned char *)hdr->datastart;
    paramstr = "TotParamCnt=[d] \n"
      "TotDataCnt=[d] \n"
      "Res1=[d]\n"
      "ParamCnt=[d] \n"
      "ParamOff=[d] \n"
      "Res2=[d] \n"
      "DataCnt=[d] \n"
      "DataOff=[d] \n"
      "Res3=[d]\n"
      "Lsetup=[d]\n";
    datastr = "|Unknown ";
  } else {
    if (hdr->totparamlen + 2 > ndo->ndo_snapend - 2 ||
        hdr->paramend + 2 > ndo->ndo_snapend - 2)
      goto trunc;
    paramlen = hdr->totparamlen;
    paramstart = (unsigned char *)hdr->paramstart;
    datalen = hdr->totdatalen;
    datastart = (unsigned char *)hdr->datastart;
    paramstr = "TotParamCnt=[d] \n"
      "TotDataCnt=[d] \n"
      "MaxParmCnt=[d] \n"
      "MaxDataCnt=[d]\n"
      "MaxSCnt=[d] \n"
      "TransFlags=[w] \n"
      "Res1=[w] \n"
      "Res2=[w] \n"
      "Res3=[w]\n"
      "ParamCnt=[d] \n"
      "ParamOff=[d] \n"
      "DataCnt=[d] \n"
      "DataOff=[d] \n"
      "SUCnt=[d]\n";
    datastr = "|Name=[S]\n";
  }
  if (hdr->wordcount + 2 > ndo->ndo_snapend - 2 ||
      hdr->end + 2 > ndo->ndo_snapend - 2)
    goto trunc;
  nddissect(ndo, (unsigned char *)hdr, paramstr,
    (unsigned char *)hdr->end, unicodestr);
  if (hdr->end + 2 > ndo->ndo_snapend - 2 ||
      data->end + 2 > ndo->ndo_snapend - 2)
    goto trunc;
  bcc = data->bcc;
  ndo->ndo_printf(ndo, "smb_bcc=%u\n", bcc);
  if (bcc == 0)
    return;
  nddissect(ndo, (unsigned char *)data->end, datastr,
    maxbuf - datalen - paramlen, unicodestr);
  if (smb_strnicmp((char *)data->end, "\\MAILSLOT\\BROWSE", 16) == 0) {
    smbbrowse(ndo, paramstart, paramlen, datastart, datalen);
  } else if (smb_strnicmp((char *)data->end, "\\PIPE\\LANMAN", 12) == 0) {
    smbpipe(ndo, paramstart, paramlen, datastart, datalen);
  } else {
    if (paramlen > 0) {
      if (paramstart + paramlen > maxbuf)
        nddissect(ndo, paramstart, "|Param ",
          maxbuf, unicodestr);
      else
        nddissect(ndo, paramstart, "|Param ",
          paramstart + paramlen, unicodestr);
    }
    if (datalen > 0) {
      if (datastart + datalen > maxbuf)
        nddissect(ndo, datastart, "|Data ",
          maxbuf, unicodestr);
      else
        nddissect(ndo, datastart, "|Data ",
          datastart + datalen, unicodestr);
    }
  }
  return;
trunc:
  ndo->ndo_printf(ndo, "%s", "[|SMB]");
  return;
}