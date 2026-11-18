void transformBlock(uint8 mcuBlock)

{
  uint8 mcuBlock_local;
  
  idctRows();
  idctCols();
  switch(gScanType) {
  case PJPG_GRAYSCALE:
    copyY('\0');
    break;
  case PJPG_YH1V1:
    if (mcuBlock == '\0') {
      copyY('\0');
    }
    else if (mcuBlock == '\x01') {
      convertCb('\0');
    }
    else if (mcuBlock == '\x02') {
      convertCr('\0');
    }
    break;
  case PJPG_YH2V1:
    switch(mcuBlock) {
    case '\0':
      copyY('\0');
      break;
    case '\x01':
      copyY('@');
      break;
    case '\x02':
      upsampleCbH('\0','\0');
      upsampleCbH('\x04','@');
      break;
    case '\x03':
      upsampleCrH('\0','\0');
      upsampleCrH('\x04','@');
    }
    break;
  case PJPG_YH1V2:
    switch(mcuBlock) {
    case '\0':
      copyY('\0');
      break;
    case '\x01':
      copyY(0x80);
      break;
    case '\x02':
      upsampleCbV('\0','\0');
      upsampleCbV(' ',0x80);
      break;
    case '\x03':
      upsampleCrV('\0','\0');
      upsampleCrV(' ',0x80);
    }
    break;
  case PJPG_YH2V2:
    switch(mcuBlock) {
    case '\0':
      copyY('\0');
      break;
    case '\x01':
      copyY('@');
      break;
    case '\x02':
      copyY(0x80);
      break;
    case '\x03':
      copyY(0xc0);
      break;
    case '\x04':
      upsampleCb('\0','\0');
      upsampleCb('\x04','@');
      upsampleCb(' ',0x80);
      upsampleCb('$',0xc0);
      break;
    case '\x05':
      upsampleCr('\0','\0');
      upsampleCr('\x04','@');
      upsampleCr(' ',0x80);
      upsampleCr('$',0xc0);
    }
  }
  return;
}