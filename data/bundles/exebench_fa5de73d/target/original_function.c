void
QuaternionMult(float pfQOut[4], float pfQIn1[4], float pfQIn2[4])
{
# 215 "quaternion.c"
    pfQOut[0] = ((pfQIn2[0] * pfQIn1[0]) - (pfQIn2[1] * pfQIn1[1]) -
                   (pfQIn2[2] * pfQIn1[2]) - (pfQIn2[3] * pfQIn1[3]));




    pfQOut[1]= ((pfQIn2[1] * pfQIn1[0]) + (pfQIn2[0] * pfQIn1[1]) -
                  (pfQIn2[2] * pfQIn1[3]) + (pfQIn2[3] * pfQIn1[2]));




    pfQOut[2]= ((pfQIn2[0] * pfQIn1[2]) + (pfQIn2[1] * pfQIn1[3]) -
                  (pfQIn2[2] * pfQIn1[0]) - (pfQIn2[3] * pfQIn1[1]));




    pfQOut[3] = ((pfQIn2[0] * pfQIn1[3]) - (pfQIn2[1] * pfQIn1[2]) -
                   (pfQIn2[2] * pfQIn1[1]) + (pfQIn2[3] * pfQIn1[0]));
}