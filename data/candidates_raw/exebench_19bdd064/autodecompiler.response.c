void euler2quaternion(float phi, float theta, float psi, float q[4])
{
 float p, r;

 q[0] = phi;
 p = theta;
 r = psi;

 if (p < 0)
  p += 360;
 if (r < 0)
  r += 360;

 if ((r > 90) && (r < 270))
 {
  p = 180 - p;
  if (p < 0)
   p += 360;
 }
 else
 {
  if (p <= 180)
   q[1] = -p;
  if (p > 180)
   q[1] = 360 - p;
  if ((r >= 0) && (r <= 90))
   q[2] = r;
  else
  {
   if ((r > 90) && (r < 270))
    q[2] = 180 - r;
   else
    q[2] = r - 360;
  }
 }
}