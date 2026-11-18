void __cdecl RemoveICCProfileFromResourceBlock(StringInfo *bim_profile)
{
  size_t length = GetStringInfoLength(bim_profile);
  
  // An 8BIM resource block requires at least 12 bytes for the header 
  // (4 bytes signature, 2 bytes ID, 2 bytes padding, 4 bytes data length)
  if (length < 12)
    return;

  unsigned __int8 *datum = GetStringInfoDatum(bim_profile);
  unsigned __int8 *p = datum;
  
  // Iterate through the 8BIM resource blocks
  while (p >= datum && p < &datum[length - 12])
  {
    // Check for '8BIM' signature
    if (LocaleNCompare((const char *)p, "8BIM", 4) != 0)
      break;

    unsigned __int8 *block_start = p;
    unsigned int long_sans;   // Signature (ignored)
    unsigned __int16 id;      // Resource ID
    unsigned __int16 short_sans; // Padding (ignored)
    unsigned int count;       // Data size

    // Read the block header (MSBEndian format)
    p = PushLongPixel(MSBEndian, p, &long_sans);
    p = PushShortPixel(MSBEndian, p, &id);
    p = PushShortPixel(MSBEndian, p, &short_sans);
    p = PushLongPixel(MSBEndian, p, &count);

    // Check if the resource ID is 1039 (0x040F), which corresponds to the ICC Profile
    if (id == 1039)
    {
      // Resource data is padded to an even byte boundary
      size_t padded_count = (count + 1) & 0xFFFFFFFFFFFFFFFEULL;
      size_t block_size = padded_count + 12; // 12 bytes for the block header
      
      // Calculate the size of the remaining data after this block
      size_t remaining_length = length - (block_start - datum) - block_size;
      
      // Shift the remaining data back to overwrite the ICC profile block
      CopyMagickMemory(block_start, block_start + block_size, remaining_length);
      
      // Update the overall length of the StringInfo datum
      SetStringInfoLength(bim_profile, length - block_size);
      return;
    }

    // Advance the pointer past the resource data and any padding byte
    p += count;
    if (count & 1)
      ++p;
  }
}