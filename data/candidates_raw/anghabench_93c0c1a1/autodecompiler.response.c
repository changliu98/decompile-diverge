unsigned int HSV2RGB(unsigned short hue, unsigned char sat, unsigned char val)
{
 unsigned char H_accent = (hue % 360) / 60;
 unsigned short bottom = ((255 - sat) * val) >> 8;
 unsigned short top = val;
 unsigned char rising = ((top-bottom) * ((hue % 60) * 60) / 3600) + bottom;
 unsigned char falling = ((top-bottom) * (60 - ((hue % 60) * 60) / 3600)) / 60 + bottom;

 unsigned char r, g, b;
 switch(H_accent)
 {
  case 0:
   r = top;
   g = rising;
   b = bottom;
   break;
  case 1:
   r = falling;
   g = top;
   b = bottom;
   break;
  case 2:
   r = bottom;
   g = top;
   b = rising;
   break;
  case 3:
   r = bottom;
   g = falling;
   b = top;
   break;
  case 4:
   r = rising;
   g = bottom;
   b = top;
   break;
  case 5:
   r = top;
   g = bottom;
   b = falling;
  default:
   break;
 }
 unsigned int rgb = (g << 16) | (r << 8) | b;
 return rgb;
}