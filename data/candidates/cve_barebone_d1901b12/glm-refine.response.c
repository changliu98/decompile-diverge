int __cdecl do_bid_note(
        magic_set *ms,
        unsigned __int8 *nbuf,
        uint32_t type,
        int swap,
        uint32_t namesz,
        uint32_t descsz,
        size_t noff,
        size_t doff,
        int *flags)
{
  uint32_t i;
  uint8_t desc[20];
  const char *build_id_type;
  int ret;

  // The original function saved all parameters to local variables (msa, nbufa, etc.)
  // This is an artifact of the decompiler. We can use the parameters directly.

  // Check if the note is a GNU Build ID note (type 3, name "GNU\0")
  // Note: 's2' is assumed to be a global string literal "GNU" based on ELF standard and context.
  if (namesz != 4 || strcmp((const char *)&nbuf[noff], "GNU") != 0 || type != 3)
    return 0;

  *flags |= 0x10u;

  // Determine the Build ID type based on descriptor size
  switch (descsz)
  {
    case 8:
      build_id_type = "xxHash";
      break;
    case 16:
      build_id_type = "md5/uuid";
      break;
    case 20:
      build_id_type = "sha1";
      break;
    default:
      build_id_type = "unknown";
      break;
  }

  ret = file_printf(ms, ", BuildID[%s]=", build_id_type);
  if (ret == -1)
    return 1;

  // Copy descriptor to local buffer (bounded by descsz, max 20 bytes for standard types)
  memcpy(desc, &nbuf[doff], descsz);

  // Print the Build ID in hexadecimal format
  for (i = 0; i < descsz; ++i)
  {
    if (file_printf(ms, "%02x", desc[i]) == -1)
      return 1;
  }

  return 1;
}