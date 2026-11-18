uint8 __cdecl locateSOFMarker()
{
  uint8 status; // [rsp+Dh] [rbp-3h]
  uint8 statusa; // [rsp+Dh] [rbp-3h]
  uint8 statusb; // [rsp+Dh] [rbp-3h]
  uint8 c; // [rsp+Eh] [rbp-2h] BYREF
  uint8 v5; // [rsp+Fh] [rbp-1h]

  status = locateSOIMarker();
  if ( status )
    return status;
  statusa = processMarkers(&c);
  if ( statusa )
    return statusa;
  switch ( c )
  {
    case 0xC0u:
      statusb = readSOFMarker();
      if ( statusb )
        v5 = statusb;
      else
        v5 = 0;
      break;
    case 0xC2u:
      v5 = 37;
      break;
    case 0xC9u:
      v5 = 17;
      break;
    default:
      v5 = 20;
      break;
  }
  return v5;
}