float nabs_sf(float x)




{
 float t;
 int32_t hx;
 u_int32_t sign;
 u_int32_t high;

 do { ieee_float_shape_type gf_u; gf_u.value = (x); (hx) = gf_u.word; } while (0);
 sign=hx&0x80000000;
 hx ^=sign;
 if(hx>=0x7f800000) return(x+x);
 if(hx==0)
     return(x);

 do { ieee_float_shape_type sf_u; sf_u.word = (hx); (x) = sf_u.value; } while (0);

 if(hx<0x00800000)
   {do { ieee_float_shape_type sf_u; sf_u.word = (0x4b800000); (t) = sf_u.value; } while (0);
    t*=x; do { ieee_float_shape_type gf_u; gf_u.value = (t); (high) = gf_u.word; } while (0); do { ieee_float_shape_type sf_u; sf_u.word = (high/3+B2); (t) = sf_u.value; } while (0);
   }
 else
   do { ieee_float_shape_type sf_u; sf_u.word = (hx/3+B1); (t) = sf_u.value; } while (0);



 r=t*t/x;
 s=C+r*t;
 t*=G+F/(s+E+D/s);


 do { ieee_float_shape_type gf_u; gf_u.value = (t); (high) = gf_u.word; } while (0);
 do { ieee_float_shape_type sf_u; sf_u.word = (high|sign); (t) = sf_u.value; } while (0);
 return(t);
}