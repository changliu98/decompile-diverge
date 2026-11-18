void
_fpcvt(double arg, int *ndigit, int *exp)
{
 union {
                double d;
                struct {
   u_int32_t mantlo : 32;
   u_int32_t manthi : 20;
   u_int32_t exp : 11;
   u_int32_t sign : 1;
  } s;
        } u;

 u.d = arg;
 *ndigit = 0;
 *exp = 0;
}