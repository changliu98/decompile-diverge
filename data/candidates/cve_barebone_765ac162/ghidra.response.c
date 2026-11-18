void print_trans(netdissect_options *ndo,u_char *words,u_char *data1,u_char *buf,u_char *maxbuf)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int iVar5;
  u_char *local_d8;
  u_char *local_b8;
  u_char *local_98;
  int paramlen;
  int datalen;
  u_char *w;
  u_char *param;
  u_char *data;
  char *f4;
  char *f3;
  char *f2;
  char *f1;
  u_int bcc;
  u_char *maxbuf_local;
  u_char *buf_local;
  u_char *data1_local;
  u_char *words_local;
  netdissect_options *ndo_local;
  
  if (request == 0) {
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < words + 0xf))
    goto LAB_00101a3d;
    uVar1 = *(ushort *)(words + 7);
    uVar2 = *(ushort *)(words + 9);
    uVar3 = *(ushort *)(words + 0xd);
    uVar4 = *(ushort *)(words + 0xf);
    f1 = 
    "TotParamCnt=[d] \nTotDataCnt=[d] \nRes1=[d]\nParamCnt=[d] \nParamOff=[d] \nRes2=[d] \nDataCnt=[d] \nDataOff=[d] \nRes3=[d]\nLsetup=[d]\n"
    ;
    f2 = "|Unknown ";
  }
  else {
    if ((ndo->ndo_snapend < ndo->ndo_snapend + -2) || (ndo->ndo_snapend + -2 < words + 0x19))
    goto LAB_00101a3d;
    uVar1 = *(ushort *)(words + 0x13);
    uVar2 = *(ushort *)(words + 0x15);
    uVar3 = *(ushort *)(words + 0x17);
    uVar4 = *(ushort *)(words + 0x19);
    f1 = 
    "TotParamCnt=[d] \nTotDataCnt=[d] \nMaxParmCnt=[d] \nMaxDataCnt=[d]\nMaxSCnt=[d] \nTransFlags=[w] \nRes1=[w] \nRes2=[w] \nRes3=[w]\nParamCnt=[d] \nParamOff=[d] \nDataCnt=[d] \nDataOff=[d] \nSUCnt=[d]\n"
    ;
    f2 = "|Name=[S]\n";
  }
  data = buf + (int)(uint)uVar4;
  param = buf + (int)(uint)uVar2;
  datalen = (int)uVar3;
  paramlen = (int)uVar1;
  local_98 = maxbuf;
  if (words + (long)(int)((uint)*words << 1) + 1 <= maxbuf) {
    local_98 = words + (long)(int)((uint)*words << 1) + 1;
  }
  smb_fdata(ndo,words + 1,f1,local_98,unicodestr);
  if ((ndo->ndo_snapend + -2 <= ndo->ndo_snapend) && (data1 <= ndo->ndo_snapend + -2)) {
    uVar1 = *(ushort *)data1;
    (*ndo->ndo_printf)(ndo,"smb_bcc=%u\n",(ulong)(uint)uVar1);
    if (uVar1 == 0) {
      return;
    }
    smb_fdata(ndo,data1 + 2,f2,maxbuf + -(long)(paramlen + datalen),unicodestr);
    iVar5 = strcmp((char *)(data1 + 2),"\\MAILSLOT\\BROWSE");
    if (iVar5 == 0) {
      print_browse(ndo,param,paramlen,data,datalen);
      return;
    }
    iVar5 = strcmp((char *)(data1 + 2),"\\PIPE\\LANMAN");
    if (iVar5 == 0) {
      print_ipc(ndo,param,paramlen,data,datalen);
      return;
    }
    if (paramlen != 0) {
      local_b8 = maxbuf;
      if (param + paramlen <= maxbuf) {
        local_b8 = param + paramlen;
      }
      smb_fdata(ndo,param,"|Param ",local_b8,unicodestr);
    }
    if (datalen == 0) {
      return;
    }
    local_d8 = maxbuf;
    if (data + datalen <= maxbuf) {
      local_d8 = data + datalen;
    }
    smb_fdata(ndo,data,"|Data ",local_d8,unicodestr);
    return;
  }
LAB_00101a3d:
  (*ndo->ndo_printf)(ndo,"%s","[|SMB]");
  return;
}