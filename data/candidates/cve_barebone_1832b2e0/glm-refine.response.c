int __cdecl xrdp_wm_parse_domain_information(char *originalDomainInfo, int comboMax, int decode, char *resultBuffer)
{
  char index[2] = {0}; // 2-byte buffer to hold a single char + null terminator
  int comboxindex;
  int pos;
  int ret = 0;

  // Clear the result buffer (max 256 bytes)
  memset(resultBuffer, 0, 0x100u);

  // Check if the string starts with an underscore '_'
  if (*originalDomainInfo == '_')
  {
    // Search for the delimiter "__" starting from the second character
    pos = g_pos(originalDomainInfo + 1, "__");

    if (pos <= 0)
    {
      // Delimiter not found: copy the rest of the string (up to 255 chars)
      g_strncpy(resultBuffer, originalDomainInfo + 1, 255);
    }
    else
    {
      // Delimiter found: extract the index if decoding is requested
      if (decode)
      {
        // Copy exactly 1 character from right after "__"
        g_strncpy(index, &originalDomainInfo[pos + 3], 1);
        
        // Convert hex string to integer
        comboxindex = g_htoi(index);
        
        // Validate the index against the combo box bounds
        if (comboxindex > 0 && comboxindex < comboMax)
          ret = comboxindex;
      }
      
      // Copy the domain name portion (up to the delimiter)
      g_strncpy(resultBuffer, originalDomainInfo + 1, pos);
    }
  }
  
  return ret;
}