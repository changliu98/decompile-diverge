int __cdecl editorSyntaxToColor(int hl)
{
  int v2; // [rsp+Ch] [rbp-4h]

  switch ( hl )
  {
    case 2:
    case 3:
      v2 = 36;
      break;
    case 4:
      v2 = 33;
      break;
    case 5:
      v2 = 32;
      break;
    case 6:
      v2 = 35;
      break;
    case 7:
      v2 = 31;
      break;
    case 8:
      v2 = 34;
      break;
    default:
      v2 = 37;
      break;
  }
  return v2;
}