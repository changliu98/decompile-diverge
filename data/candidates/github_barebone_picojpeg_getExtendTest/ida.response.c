uint16 __cdecl getExtendTest(uint8 i)
{
  uint16 v2; // [rsp+Eh] [rbp-2h]

  switch ( i )
  {
    case 0u:
      v2 = 0;
      break;
    case 1u:
      v2 = 1;
      break;
    case 2u:
      v2 = 2;
      break;
    case 3u:
      v2 = 4;
      break;
    case 4u:
      v2 = 8;
      break;
    case 5u:
      v2 = 16;
      break;
    case 6u:
      v2 = 32;
      break;
    case 7u:
      v2 = 64;
      break;
    case 8u:
      v2 = 128;
      break;
    case 9u:
      v2 = 256;
      break;
    case 0xAu:
      v2 = 512;
      break;
    case 0xBu:
      v2 = 1024;
      break;
    case 0xCu:
      v2 = 2048;
      break;
    case 0xDu:
      v2 = 4096;
      break;
    case 0xEu:
      v2 = 0x2000;
      break;
    case 0xFu:
      v2 = 0x4000;
      break;
    default:
      v2 = 0;
      break;
  }
  return v2;
}