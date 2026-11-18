unsigned char locateSOFMarker(void)
{
  unsigned char c;
  unsigned char status;


  status = locateSOIMarker();
  if (status != 0)
    return status;


  status = processMarkers(&c);
  if (status != 0)
    return status;


  switch (c)
  {
    case 0xC0:
      status = readSOFMarker();
      if (status != 0)
        return status;
      break;

    case 0xC1:
      return 20;

    case 0xC2:
      return 37;

    case 0xC9:
      return 17;

    default:
      return 20;
  }

  return 0;
}