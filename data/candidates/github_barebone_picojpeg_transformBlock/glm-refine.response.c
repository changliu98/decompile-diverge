void __cdecl transformBlock(uint8 mcuBlock)
{
  idctRows();
  idctCols();

  switch (gScanType)
  {
    case SCAN_444:
      if (mcuBlock == BLOCK_Y0)
        copyY(0);
      else if (mcuBlock == BLOCK_CB)
        convertCb(0);
      else if (mcuBlock == BLOCK_CR)
        convertCr(0);
      break;

    case SCAN_422:
      switch (mcuBlock)
      {
        case BLOCK_Y0: copyY(0);      break;
        case BLOCK_Y1: copyY(0x40);   break;
        case BLOCK_Y2: copyY(0x80);   break;
        case BLOCK_Y3: copyY(0xC0);   break;
        case BLOCK_CB:
          upsampleCbH(0, 0);
          upsampleCbH(4, 0x40);
          break;
        case BLOCK_CR:
          upsampleCrH(0, 0);
          upsampleCrH(4, 0x40);
          break;
        default: return;
      }
      break;

    case SCAN_411:
      switch (mcuBlock)
      {
        case BLOCK_Y0: copyY(0);      break;
        case BLOCK_Y1: copyY(0x40);   break;
        case BLOCK_Y2: copyY(0x80);   break;
        case BLOCK_Y3: copyY(0xC0);   break;
        case BLOCK_CB:
          upsampleCb(0, 0);
          upsampleCb(4, 0x40);
          upsampleCb(0x20, 0x80);
          upsampleCb(0x24, 0xC0);
          break;
        case BLOCK_CR:
          upsampleCr(0, 0);
          upsampleCr(4, 0x40);
          upsampleCr(0x20, 0x80);
          upsampleCr(0x24, 0xC0);
          break;
        default: return;
      }
      break;

    case SCAN_440:
      switch (mcuBlock)
      {
        case BLOCK_Y0: copyY(0);      break;
        case BLOCK_Y1: copyY(0x40);   break;
        case BLOCK_Y2: copyY(0x80);   break;
        case BLOCK_Y3: copyY(0xC0);   break;
        case BLOCK_CB:
          upsampleCbV(0, 0);
          upsampleCbV(0x20, 0x80);
          break;
        case BLOCK_CR:
          upsampleCrV(0, 0);
          upsampleCrV(0x20, 0x80);
          break;
        default: return;
      }
      break;

    case SCAN_420:
      switch (mcuBlock)
      {
        case BLOCK_Y0: copyY(0);      break;
        case BLOCK_Y1: copyY(0x40);   break;
        case BLOCK_Y2: copyY(0x80);   break;
        case BLOCK_Y3: copyY(0xC0);   break;
        case BLOCK_CB:
          upsampleCb(0, 0);
          upsampleCb(4, 0x40);
          upsampleCb(0x20, 0x80);
          upsampleCb(0x24, 0xC0);
          break;
        case BLOCK_CR:
          upsampleCr(0, 0);
          upsampleCr(4, 0x40);
          upsampleCr(0x20, 0x80);
          upsampleCr(0x24, 0xC0);
          break;
        default: return;
      }
      break;

    default:
      return;
  }
}