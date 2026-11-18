#include <stdio.h>

char *
sgml__utf8_get_char(const char *in, int *chr)
{
  if ( (in[0]&0xe0) == 0xc0 && ((in[1]&0xc0) == 0x80) )
  { *chr = ((in[0]&0x1f) << 6)|((in[1]&0x3f) << 0);
    return (char *)in+2;
  }

  if ( (in[0]&0xf0) == 0xe0 && ((in[1]&0xc0) == 0x80) && ((in[2]&0xc0) == 0x80) )
  { *chr = ((in[0]&0xf) << 12)|((in[1]&0x3f) << 6)|((in[2]&0x3f) << 0);
    return (char *)in+3;
  }

  if ( (in[0]&0xf8) == 0xf0 && ((in[1]&0xc0) == 0x80) && ((in[2]&0xc0) == 0x80) && ((in[3]&0xc0) == 0x80) )
  { *chr = ((in[0]&0x7) << 18)|((in[1]&0x3f) << 12)|((in[2]&0x3f) << 6)|((in[3]&0x3f) << 0);
    return (char *)in+4;
  }

  if ( (in[0]&0xfc) == 0xf8 && ((in[1]&0xc0) == 0x80) && ((in[2]&0xc0) == 0x80) && ((in[3]&0xc0) == 0x80) && ((in[4]&0xc0) == 0x80) )
  { *chr = ((in[0]&0x3) << 24)|((in[1]&0x3f) << 18)|((in[2]&0x3f) << 12)|((in[3]&0x3f) << 6)|((in[4]&0x3f) << 0);
    return (char *)in+5;
  }

  if ( (in[0]&0xfe) == 0xfc && ((in[1]&0xc0) == 0x80) && ((in[2]&0xc0) == 0x80) && ((in[3]&0xc0) == 0x80) && ((in[4]&0xc0) == 0x80) && ((in[5]&0xc0) == 0x80) )
  { *chr = ((in[0]&0x1) << 30)|((in[1]&0x3f) << 24)|((in[2]&0x3f) << 18)|((in[3]&0x3f) << 12)|((in[4]&0x3f) << 6)|((in[5]&0x3f) << 0);
    return (char *)in+4;
  }

  *chr = *in;

  return (char *)in+1;
}
