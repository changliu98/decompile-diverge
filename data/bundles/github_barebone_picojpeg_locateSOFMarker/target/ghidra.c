/* WARNING: Unknown calling convention -- yet parameter storage is locked */

uint8 locateSOFMarker(void)

{
  uint8 status;
  uint8 c;
  uint8 local_9;
  
  local_9 = locateSOIMarker();
  if ((local_9 == '\0') && (local_9 = processMarkers(&c), local_9 == '\0')) {
    switch(c) {
    case 0xc0:
      local_9 = readSOFMarker();
      if (local_9 == '\0') {
        local_9 = '\0';
      }
      break;
    case 0xc1:
    default:
      local_9 = '\x14';
      break;
    case 0xc2:
      local_9 = '%';
      break;
    case 0xc9:
      local_9 = '\x11';
    }
  }
  return local_9;
}