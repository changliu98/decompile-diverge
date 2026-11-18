void
print_trans(struct smbhead *smbhp, char *data, char *name, char *base, char *max)
{
 int bcc;
 int tot_param_cnt, tot_data_cnt;
 int param_cnt, data_cnt;
 char *param, *data1, *param_base, *data_base;
 char *fmt, *fmt1, *fmt2, *fmt3, *fmt4, *fmt5, *fmt6, *fmt7, *fmt8;
 char *fmt9, *fmt10, *fmt11, *fmt12, *fmt13, *fmt14, *fmt15, *fmt16;

 data1 = data + 1;
 if (request) {
  if ((unsigned int)(smbhp->smb_hdroff - 2) > (unsigned int)smbhp->smb_hdroff ||
      (unsigned int)(smbhp->smb_hdroff + sizeof(struct smb_hdr) + 24) > (unsigned int)smbhp->smb_hdroff)
   return trunc();
  tot_param_cnt = (((((unsigned short)((*((unsigned char *)data1 + 19) << 8) | *((unsigned char *)data1 + 18))))));
  param_base = base + (((((unsigned short)((*((unsigned char *)data1 + 21) << 8) | *((unsigned char *)data1 + 20))))));
  tot_data_cnt = (((((unsigned short)((*((unsigned char *)data1 + 23) << 8) | *((unsigned char *)data1 + 22))))));
  data_base = base + (((((unsigned short)((*((unsigned char *)data1 + 25) << 8) | *((unsigned char *)data1 + 24))))));
  fmt = "TotParamCnt=[d] \nTotDataCnt=[d] \nMaxParamCnt=[d] \nMaxDataCnt=[d] \nMaxMpxCount=[d] \nVcNumber=[d] \nTreeId=[d] \nProcId=[d] \nSessionId=[d] \nSigniture=[d] \nFlags=[d] \nFlags2=[d] \nCommand=[d] \nCid=[d] \nPid=[d] \nTid=[d] \nUid=[d] \nMid=[d] \nWordCount=[d] \n";
  fmt1 = "|Name=[S]\n";
  fmt2 = "|Param ";
  fmt3 = "|Data ";
 } else {
  if ((unsigned int)(smbhp->smb_hdroff - 2) > (unsigned int)smbhp->smb_hdroff ||
      (unsigned int)(smbhp->smb_hdroff + sizeof(struct smb_hdr) + 14) > (unsigned int)smbhp->smb_hdroff)
   return trunc();
  tot_param_cnt = (((((unsigned short)((*((unsigned char *)data1 + 7) << 8) | *((unsigned char *)data1 + 6))))));
  param_base = base + (((((unsigned short)((*((unsigned char *)data1 + 9) << 8) | *((unsigned char *)data1 + 8))))));
  tot_data_cnt = (((((unsigned short)((*((unsigned char *)data1 + 13) << 8) | *((unsigned char *)data1 + 12))))));
  data_base = base + (((((unsigned short)((*((unsigned char *)data1 + 15) << 8) | *((unsigned char *)data1 + 14))))));
  fmt = "TotParamCnt=[d] \nTotDataCnt=[d] \nRes1=[d] \nCommand=[d] \nCid=[d] \nPid=[d] \nTid=[d] \nUid=[d] \nMid=[d] \nWordCount=[d] \n";
  fmt1 = "|Unknown ";
  fmt2 = "|Param ";
  fmt3 = "|Data ";
 }

 smb_fdata(smbhp, data1, fmt, data1 + 1 + 2 * (*data), max, unicodestr);

 if ((unsigned int)(smbhp->smb_hdroff - 2) > (unsigned int)smbhp->smb_hdroff ||
     (unsigned int)(name) > (unsigned int)smbhp->smb_hdroff)
  return trunc();
 bcc = (((((unsigned short)((*((unsigned char *)name) << 8) | *((unsigned char *)(name) + 0))))));
 smbhp->debug(smbhp, "smb_bcc=%u\n", bcc);
 if (bcc <= 0)
  return;

 smb_fdata(smbhp, name + 2, fmt1, max - (tot_param_cnt + tot_data_cnt), unicodestr);

 if (!strcmp(name + 2, "\\\\MAILSLOT\\\\BROWSE"))
  print_browse(smbhp, param_base, tot_param_cnt, data_base, tot_data_cnt);
 else if (!strcmp(name + 2, "\\\\PIPE\\\\LANMAN"))
  print_ipc(smbhp, param_base, tot_param_cnt, data_base, tot_data_cnt);
 else {
  if (tot_param_cnt)
   smb_fdata(smbhp, param_base, fmt2, param_base + tot_param_cnt, unicodestr);
  if (tot_data_cnt)
   smb_fdata(smbhp, data_base, fmt3, data_base + tot_data_cnt, unicodestr);
 }
}