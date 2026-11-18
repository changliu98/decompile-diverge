float get_color_value(int attr, float *c, float *b, float *g)
{
 float color = 0.0;

 switch (attr & 0x3F) {
 case 0x09:
  color = c[0];
  break;
 case 0x0A:
  color = c[1];
  break;
 case 0x0C:
  color = c[2];
  break;
 case 0x11:
  color = b[0];
  break;
 case 0x12:
  color = b[1];
  break;
 case 0x14:
  color = b[2];
  break;
 case 0x21:
  color = g[0];
  break;
 case 0x22:
  color = g[1];
  break;
 case 0x24:
  color = g[2];
  break;
 }

 return color;
}