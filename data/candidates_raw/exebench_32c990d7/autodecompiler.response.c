void
fix_sign(int sign_mask, int *val)
{
 if (*val & sign_mask) {
  *val = (sign_mask << 1) - *val;
  *val *= -1;
 }
}