static int imul_dbl(unsigned long m[2])
{
    int rc;
    asm ( "imul %4; seto %b2"
          : "=a" (m[0]), "=d" (m[1]), "=q" (rc)
          : "0" (m[0]), "1" (m[1]), "2" (0) );
    return rc;
}