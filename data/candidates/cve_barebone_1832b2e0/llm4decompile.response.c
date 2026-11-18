int
xrdp_wm_parse_domain_information(char* originalDomainInfo, int comboMax,
                                 int decode, char* resultBuffer)
{
  int len;
  int index;
  int ret;
  char hindex[2];

  ret = 0;
  memset(resultBuffer, 0, 256);
  if (originalDomainInfo[0] != '_')
  {
    return 0;
  }
  originalDomainInfo++;
  len = g_pos(originalDomainInfo, "__");
  if (len > 0)
  {
    if (decode)
    {
      memset(hindex, 0, 2);
      g_strncpy(hindex, &originalDomainInfo[len + 2], 1);
      index = g_htoi(hindex);
      if ((index > 0) && (index < comboMax))
      {
        ret = index;
      }
    }
    g_strncpy(resultBuffer, originalDomainInfo, len);
  }
  else
  {
    g_strncpy(resultBuffer, originalDomainInfo, 256 - 1);
  }
  return ret;
}