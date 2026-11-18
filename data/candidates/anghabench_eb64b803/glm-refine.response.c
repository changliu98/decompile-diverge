int __cdecl file_type_to_content_type(int file_type)
{
  switch ( file_type )
  {
    case 128:
      return ct_webp;
    case 129:
      return ct_unknown;
    case 130:
      return ct_png;
    case 131:
      return ct_pdf;
    case 132:
      return ct_partial;
    case 133:
      return ct_mp4;
    case 134:
      return ct_mp3;
    case 135:
      return ct_mov;
    case 136:
      return ct_jpeg;
    case 137:
      return ct_gif;
    default:
      return ct_last | 0x40000000; // or equivalently: 0x40000000 | ct_last
  }
}