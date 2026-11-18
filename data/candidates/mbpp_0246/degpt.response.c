double func0(double number)

{
  double n;
  double g2;
  double g;
  double number_local;
  undefined8 local_10;
  
  if ((number != 0.0) || (NAN(number))) {
    g = number / DAT_00102010;
    g2 = DAT_00102008 + g;
    for (; (g != g2 || (NAN(g) || NAN(g2))); g = (g + number / g) / DAT_00102010) {
      g2 = g;
    }
    local_10 = g;
  }
  else {
    local_10 = 0.0;
  }
  return local_10;
}