void __cdecl Vector_Cross_Product(float *vectorOut, float *v1, float *v2)
{
    vectorOut[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    vectorOut[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    vectorOut[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}