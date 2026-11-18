void __cdecl print_attr_string(netdissect_options *ndo, const u_char *data, u_int length, u_short attr_code)
{
  const u_char *cursor;
  u_int remaining_len;
  u_int i;

  // Check for buffer overflow or invalid length
  if (length == 0 || data > ndo->ndo_snapend - length)
  {
    ndo->ndo_printf(ndo, "%s", " [|radius]");
    return;
  }

  cursor = data;
  remaining_len = length;

  // Attribute 58: Egress-VLANID (RFC 4675)
  if (attr_code == 58)
  {
    const char *tag_str = tok2str(&rfc4675_tagged, "Unknown tag", *data);
    ndo->ndo_printf(ndo, "%s (0x%02x) ", tag_str, *data);
    cursor++;
    remaining_len--;
  }
  // Attribute 66 or 67: Egress-VLAN-Name or User-Priority-Table
  else if ((unsigned int)attr_code - 66 < 2)
  {
    // Fall-through to string printing
  }
  // Attribute 69: Tunnel-Password
  else if (attr_code == 69)
  {
    if (length < 3)
    {
      ndo->ndo_printf(ndo, "%s", " [|radius]");
      return;
    }
    
    if (*data && *data <= 0x1F)
      ndo->ndo_printf(ndo, "Tag[%u] ", *data);
    else
      ndo->ndo_printf(ndo, "Tag[Unused] ");
      
    ndo->ndo_printf(ndo, "Salt %u ", _byteswap_ushort(*(unsigned short *)(data + 1)));
    
    cursor += 3;
    remaining_len -= 3;
  }
  // Attributes 81, 82, 90, 91: Fall-through to string printing
  else if ((unsigned int)attr_code - 81 >= 2 && (unsigned int)attr_code - 90 >= 2)
  {
    // Fall-through to string printing
  }

  // Handle Tag byte for generic attributes (if not skipped above)
  if (attr_code != 58 && attr_code != 69 && *data <= 0x1F)
  {
    if (*data)
      ndo->ndo_printf(ndo, "Tag[%u] ", *data);
    else
      ndo->ndo_printf(ndo, "Tag[Unused] ");
      
    cursor++;
    remaining_len--;
  }

  // Print the remaining string payload, replacing non-printable characters with '.'
  for (i = 0; i < remaining_len && *cursor; ++i)
  {
    u_char c = *cursor;
    if (c >= 0x20 && c <= 0x7E)
      ndo->ndo_printf(ndo, "%c", c);
    else
      ndo->ndo_printf(ndo, "%c", '.');
    cursor++;
  }
}