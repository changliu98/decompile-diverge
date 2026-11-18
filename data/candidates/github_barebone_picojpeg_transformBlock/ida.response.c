void __cdecl transformBlock(uint8 mcuBlock)
{
  idctRows();
  idctCols();
  switch ( gScanType )
  {
    case 0:
      goto LABEL_18;
    case 1:
      if ( mcuBlock )
      {
        if ( mcuBlock == 1 )
        {
          convertCb(0);
        }
        else if ( mcuBlock == 2 )
        {
          convertCr(0);
        }
      }
      else
      {
LABEL_18:
        copyY(0);
      }
      break;
    case 2:
      switch ( mcuBlock )
      {
        case 0u:
          goto LABEL_18;
        case 1u:
          goto LABEL_14;
        case 2u:
          upsampleCbH(0, 0);
          upsampleCbH(4u, 0x40u);
          break;
        case 3u:
          upsampleCrH(0, 0);
          upsampleCrH(4u, 0x40u);
          break;
        default:
          return;
      }
      break;
    case 3:
      switch ( mcuBlock )
      {
        case 0u:
          goto LABEL_18;
        case 1u:
          goto LABEL_10;
        case 2u:
          upsampleCbV(0, 0);
          upsampleCbV(0x20u, 0x80u);
          break;
        case 3u:
          upsampleCrV(0, 0);
          upsampleCrV(0x20u, 0x80u);
          break;
        default:
          return;
      }
      break;
    case 4:
      switch ( mcuBlock )
      {
        case 0u:
          goto LABEL_18;
        case 1u:
LABEL_14:
          copyY(0x40u);
          break;
        case 2u:
LABEL_10:
          copyY(0x80u);
          break;
        case 3u:
          copyY(0xC0u);
          break;
        case 4u:
          upsampleCb(0, 0);
          upsampleCb(4u, 0x40u);
          upsampleCb(0x20u, 0x80u);
          upsampleCb(0x24u, 0xC0u);
          break;
        case 5u:
          upsampleCr(0, 0);
          upsampleCr(4u, 0x40u);
          upsampleCr(0x20u, 0x80u);
          upsampleCr(0x24u, 0xC0u);
          break;
        default:
          return;
      }
      break;
    default:
      return;
  }
}