void do_iccprofile_item(deark *c,lctx *d,int64_t pos,int64_t len)
{
  ulong selector_value;
  dbuf *profile_file_handle;
  
  // Ensure the segment has at least a 4-byte selector header
  if (3 < len) {
    // Read the 4-byte big-endian selector value from the current position
    selector_value = dbuf_getu32be(c->infile,pos);
    // Log the ICC profile segment details: selector and remaining data length
    de_dbg(c,"ICC profile segment, selector=%d, data len=%d",selector_value & 0xffffffff,
           len - 4U & 0xffffffff);
    
    // If selector is 0, this is the start of a new ICC profile
    if (selector_value == 0) {
      // Create a new output file for the ICC profile with extension "icc"
      profile_file_handle = dbuf_create_output_file(c,"icc",(de_finfo *)0x0,1);
      // Store the file handle in the context for subsequent segments
      d->iccprofile_file = profile_file_handle;
    }
    // If selector is not 0 and not 1, the profile data is invalid or corrupted
    else if (selector_value != 1) {
      // Close the previously opened ICC profile file
      dbuf_close(d->iccprofile_file);
      // Reset the file handle to null to indicate no active profile
      d->iccprofile_file = (dbuf *)0x0;
      // Exit early as the profile is invalid
      return;
    }
    
    // Copy the remaining data (excluding the 4-byte selector) to the ICC profile file
    // This handles both the initial segment (selector=0) and continuation segments (selector=1)
    dbuf_copy(c->infile,pos + 4,len - 4U,d->iccprofile_file);
  }
}