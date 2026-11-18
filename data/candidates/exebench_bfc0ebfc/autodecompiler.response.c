void
utf8_int_string(unsigned int c, char* utf8)
{
  if(!utf8)
    return;

  utf8[0]=0;


  if(c < 0x80) {
    utf8[0]=(char)c;
    utf8[1]=0;
  } else if(c < 0x800) {

    utf8[0] = (char)(0xC0 | ((c & 0x7C0) >> 6));
    utf8[1] = (char)(0x80 | (c & 0x3F));
    utf8[2]=0;
  } else if(c < 0x10000) {

    utf8[0] = (char)(0xE0 | ((c & 0xF000) >> 12));
    utf8[1] = (char)(0x80 | ((c & 0xFC0) >> 6));
    utf8[2] = (char)(0x80 | (c & 0x3F));
    utf8[3]=0;
  } else if(c < 0x200000) {

    utf8[0] = (char)(0xF0 | ((c & 0x1C0000) >> 18));
    utf8[1] = (char)(0x80 | ((c & 0x3F000) >> 12));
    utf8[2] = (char)(0x80 | ((c & 0xFC0) >> 6));
    utf8[3] = (char)(0x80 | (c & 0x3F));
    utf8[4]=0;
  }
}