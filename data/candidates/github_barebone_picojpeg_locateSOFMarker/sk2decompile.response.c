unsigned char locateSOFMarker(void) {
  unsigned char retval;
  unsigned char marker;
  unsigned char err;
  retval = locateSOIMarker();
  if (retval) return retval;
  retval = processMarkers(&marker);
  if (retval) return retval;
  switch (marker) {
    case 0xC0:
      retval = readSOFMarker();
      if (retval)
        err = retval;
      else
        err = 0;
      break;
    case 0xC2:
      err = 0x25;
      break;
    case 0xC9:
      err = 0x11;
      break;
    default:
      err = 0x14;
      break;
  }
  return err;
}