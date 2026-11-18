int __cdecl xrdp_wm_parse_domain_information(char *originalDomainInfo, int comboMax, int decode, char *resultBuffer)
{
  char index[2]; // [rsp+Ah] [rbp-26h] BYREF
  int comboxindex; // [rsp+Ch] [rbp-24h]
  int pos; // [rsp+10h] [rbp-20h]
  int ret; // [rsp+14h] [rbp-1Ch]
  char *resultBuffera; // [rsp+18h] [rbp-18h]
  int decodea; // [rsp+20h] [rbp-10h]
  int comboMaxa; // [rsp+24h] [rbp-Ch]
  char *originalDomainInfoa; // [rsp+28h] [rbp-8h]

  originalDomainInfoa = originalDomainInfo;
  comboMaxa = comboMax;
  decodea = decode;
  resultBuffera = resultBuffer;
  ret = 0;
  memset(resultBuffer, 0, 0x100uLL);
  if ( *originalDomainInfo == 95 )
  {
    pos = g_pos(originalDomainInfoa + 1, "__");
    if ( pos <= 0 )
    {
      g_strncpy(resultBuffera, originalDomainInfoa + 1, 255);
    }
    else
    {
      if ( decodea )
      {
        memset(index, 0, sizeof(index));
        g_strncpy(index, &originalDomainInfoa[pos + 3], 1);
        comboxindex = g_htoi(index);
        if ( comboxindex > 0 && comboxindex < comboMaxa )
          ret = comboxindex;
      }
      g_strncpy(resultBuffera, originalDomainInfoa + 1, pos);
    }
  }
  return ret;
}