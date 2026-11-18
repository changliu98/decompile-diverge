
int u_get(int *up,char *s) {
  unsigned char *t=(unsigned char*)s;
  if(*t<0x80) {*up=t[0]; return 1;}
  if(*t<0xC0) return 0;
  if(*t<0xE0) {*up=(((t[0]&0x1F)<<6)|(t[1]&0x3F)); return (*up&0xFFFFFF80)?2:0;}
  if(*t<0xF0) {*up=((((((t[0]&0xF)<<6)|(t[1]&0x3F)))<<6)|(t[2]&0x3F)); return (*up&0xFFFFF800)?3:0;}
  if(*t<0xF8) {*up=(((((((((t[0]&0x7)<<6)|(t[1]&0x3F)))<<6)|(t[2]&0x3F)))<<6)|(t[3]&0x3F)); return (*up&0xFFFF0000)?4:0;}
  if(*t<0xFC) {*up=((((((((((((t[0]&0x3)<<6)|(t[1]&0x3F)))<<6)|(t[2]&0x3F)))<<6)|(t[3]&0x3F)))<<6)|(t[4]&0x3F)); return (*up&0xFFE00000)?5:0;}
  if(*t<0xFE) {*up=(((((((((((((((t[0]&0x1)<<6)|(t[1]&0x3F)))<<6)|(t[2]&0x3F)))<<6)|(t[3]&0x3F)))<<6)|(t[4]&0x3F)))<<6)|(t[5]&0x3F)); return (*up&0xFC000000)?6:0;}
  return 0;
}
