void __cdecl print_trans(
        netdissect_options *ndo,
        const u_char *words,
        const u_char *data1,
        const u_char *buf,
        const u_char *maxbuf)
{
  const u_char *param;
  const u_char *data;
  const char *f1;
  const char *f2;
  int paramlen;
  int datalen;
  u_int bcc;
  u_int word_count;

  // Check for packet truncation based on request type
  if (request)
  {
    if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || words + 25 > ndo->ndo_snapend - 2)
      goto trunc;

    paramlen = *(unsigned __int16 *)(words + 19);
    param    = &buf[*(unsigned __int16 *)(words + 21)];
    datalen  = *(unsigned __int16 *)(words + 23);
    data     = &buf[*(unsigned __int16 *)(words + 25)];

    f1 = "TotParamCnt=[d] \n"
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
    f2 = "|Name=[S]\n";
  }
  else
  {
    if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || words + 15 > ndo->ndo_snapend - 2)
      goto trunc;

    paramlen = *(unsigned __int16 *)(words + 7);
    param    = &buf[*(unsigned __int16 *)(words + 9)];
    datalen  = *(unsigned __int16 *)(words + 13);
    data     = &buf[*(unsigned __int16 *)(words + 15)];

    f1 = "TotParamCnt=[d] \n"
         "TotDataCnt=[d] \n"
         "Res1=[d]\n"
         "ParamCnt=[d] \n"
         "ParamOff=[d] \n"
         "Res2=[d] \n"
         "DataCnt=[d] \n"
         "DataOff=[d] \n"
         "Res3=[d]\n"
         "Lsetup=[d]\n";
    f2 = "|Unknown ";
  }

  // Parse SMB word count and format the structure
  word_count = *words;
  const u_char *end_words = &words[2 * word_count + 1];
  smb_fdata(ndo, words + 1, f1, (end_words <= maxbuf) ? end_words : maxbuf, unicodestr);

  // Check truncation for BCC (Byte Count) area
  if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || data1 > ndo->ndo_snapend - 2)
    goto trunc;

  bcc = *(unsigned __int16 *)data1;
  ndo->ndo_printf(ndo, "smb_bcc=%u\n", bcc);

  if (bcc)
  {
    const u_char *trans_data = data1 + 2;
    smb_fdata(ndo, trans_data, f2, &maxbuf[-datalen - paramlen], unicodestr);

    if (!strcmp((const char *)trans_data, "\\MAILSLOT\\BROWSE"))
    {
      print_browse(ndo, param, paramlen, data, datalen);
    }
    else if (!strcmp((const char *)trans_data, "\\PIPE\\LANMAN"))
    {
      print_ipc(ndo, param, paramlen, data, datalen);
    }
    else
    {
      if (paramlen)
      {
        const u_char *end_param = &param[paramlen];
        smb_fdata(ndo, param, "|Param ", (end_param <= maxbuf) ? end_param : maxbuf, unicodestr);
      }
      if (datalen)
      {
        const u_char *end_data = &data[datalen];
        smb_fdata(ndo, data, "|Data ", (end_data <= maxbuf) ? end_data : maxbuf, unicodestr);
      }
    }
  }
  return;

trunc:
  ndo->ndo_printf(ndo, "%s", "[|SMB]");
}