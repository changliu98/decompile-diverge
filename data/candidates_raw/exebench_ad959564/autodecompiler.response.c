static int
expand_char(char *buf, int flags, char c)
{
 int n;

 switch (c) {
 case 0x7f:
  if (flags & 0x40) {
   buf[0] = '\b';
   n = 1;
  } else {
   buf[0] = c;
   n = 1;
  }
  break;
 case '\b':
  if (flags & 0x80) {
   buf[0] = '\x7f';
   n = 1;
  } else {
   buf[0] = c;
   n = 1;
  }
  break;
 case '\r':
  if (flags & 0x01) {
   buf[0] = '\n';
   n = 1;
  } else if (flags & 0x02) {
   buf[0] = '\r';
   buf[1] = '\n';
   n = 2;
  } else if (flags & 0x04) {
   n = 0;
  } else {
   buf[0] = c;
   n = 1;
  }
  break;
 case '\n':
  if (flags & 0x08) {
   buf[0] = '\r';
   n = 1;
  } else if (flags & 0x10) {
   buf[0] = '\r';
   buf[1] = '\n';
   n = 2;
  } else if (flags & 0x20) {
   n = 0;
  } else {
   buf[0] = c;
   n = 1;
  }
  break;
 default:
  buf[0] = c;
  n = 1;
 }

 return (n);
}