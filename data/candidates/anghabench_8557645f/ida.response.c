const char *__cdecl ata_err_string(unsigned int err_mask)
{
  if ( (AC_ERR_HOST_BUS & err_mask) != 0 )
    return "host bus error";
  if ( (AC_ERR_ATA_BUS & err_mask) != 0 )
    return "ATA bus error";
  if ( (AC_ERR_TIMEOUT & err_mask) != 0 )
    return "timeout";
  if ( (AC_ERR_HSM & err_mask) != 0 )
    return "HSM violation";
  if ( (AC_ERR_SYSTEM & err_mask) != 0 )
    return "internal error";
  if ( (AC_ERR_MEDIA & err_mask) != 0 )
    return "media error";
  if ( (AC_ERR_INVALID & err_mask) != 0 )
    return "invalid argument";
  if ( (AC_ERR_DEV & err_mask) != 0 )
    return "device error";
  if ( (AC_ERR_NCQ & err_mask) != 0 )
    return "NCQ error";
  if ( (AC_ERR_NODEV_HINT & err_mask) != 0 )
    return "Polling detection error";
  return "unknown error";
}