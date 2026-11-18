void __cdecl print_trans(
        netdissect_options *ndo,
        const u_char *words,
        const u_char *data1,
        const u_char *buf,
        const u_char *maxbuf)
{
  u_char *v5; // [rsp+50h] [rbp-80h]
  int paramlen; // [rsp+60h] [rbp-70h]
  int datalen; // [rsp+64h] [rbp-6Ch]
  const u_char *param; // [rsp+70h] [rbp-60h]
  const u_char *data; // [rsp+78h] [rbp-58h]
  const char *f2; // [rsp+90h] [rbp-40h]
  const char *f1; // [rsp+98h] [rbp-38h]
  u_int bcc; // [rsp+A4h] [rbp-2Ch]

  if ( request )
  {
    if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend || words + 25 > ndo->ndo_snapend - 2 )
    {
trunc:
      ndo->ndo_printf(ndo, "%s", "[|SMB]");
      return;
    }
    paramlen = *(unsigned __int16 *)(words + 19);
    param = &buf[*(unsigned __int16 *)(words + 21)];
    datalen = *(unsigned __int16 *)(words + 23);
    data = &buf[*(unsigned __int16 *)(words + 25)];
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
    if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend || words + 15 > ndo->ndo_snapend - 2 )
      goto trunc;
    paramlen = *(unsigned __int16 *)(words + 7);
    param = &buf[*(unsigned __int16 *)(words + 9)];
    datalen = *(unsigned __int16 *)(words + 13);
    data = &buf[*(unsigned __int16 *)(words + 15)];
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
  v5 = (u_char *)(words + 1);
  if ( &words[2 * *words + 1] <= maxbuf )
    smb_fdata(ndo, v5, f1, &words[2 * *words + 1], unicodestr);
  else
    smb_fdata(ndo, v5, f1, maxbuf, unicodestr);
  if ( ndo->ndo_snapend - 2 > ndo->ndo_snapend || data1 > ndo->ndo_snapend - 2 )
    goto trunc;
  bcc = *(unsigned __int16 *)data1;
  ndo->ndo_printf(ndo, "smb_bcc=%u\n", *(unsigned __int16 *)data1);
  if ( bcc )
  {
    smb_fdata(ndo, data1 + 2, f2, &maxbuf[-datalen - paramlen], unicodestr);
    if ( !strcmp((const char *)data1 + 2, "\\MAILSLOT\\BROWSE") )
    {
      print_browse(ndo, param, paramlen, data, datalen);
    }
    else if ( !strcmp((const char *)data1 + 2, "\\PIPE\\LANMAN") )
    {
      print_ipc(ndo, param, paramlen, data, datalen);
    }
    else
    {
      if ( paramlen )
      {
        if ( &param[paramlen] <= maxbuf )
          smb_fdata(ndo, param, "|Param ", &param[paramlen], unicodestr);
        else
          smb_fdata(ndo, param, "|Param ", maxbuf, unicodestr);
      }
      if ( datalen )
      {
        if ( &data[datalen] <= maxbuf )
          smb_fdata(ndo, data, "|Data ", &data[datalen], unicodestr);
        else
          smb_fdata(ndo, data, "|Data ", maxbuf, unicodestr);
      }
    }
  }
}