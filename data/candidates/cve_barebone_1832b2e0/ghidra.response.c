int xrdp_wm_parse_domain_information
              (char *originalDomainInfo,int comboMax,int decode,char *resultBuffer)

{
  int len;
  uint uVar1;
  char index [2];
  int comboxindex;
  int pos;
  int ret;
  char *resultBuffer_local;
  int decode_local;
  int comboMax_local;
  char *originalDomainInfo_local;
  
  ret = 0;
  memset(resultBuffer,0,0x100);
  if (*originalDomainInfo == '_') {
    len = g_pos(originalDomainInfo + 1,"__");
    if (len < 1) {
      g_strncpy(resultBuffer,originalDomainInfo + 1,0xff);
    }
    else {
      if (decode != 0) {
        memset(index,0,2);
        g_strncpy(index,originalDomainInfo + (len + 3),1);
        uVar1 = g_htoi(index);
        if ((0 < (int)uVar1) && ((int)uVar1 < comboMax)) {
          ret = uVar1;
        }
      }
      g_strncpy(resultBuffer,originalDomainInfo + 1,len);
    }
  }
  return ret;
}