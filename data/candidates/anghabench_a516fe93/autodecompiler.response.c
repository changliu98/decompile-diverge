void nvgTransformTranslate(float* M, float sx, float sy)
{
 M[0] = sx;
 M[1] = 0.0f;
 M[2] = 0.0f;
 M[3] = 0.0f;

 M[4] = 0.0f;
 M[5] = sy;
 M[6] = 0.0f;
 M[7] = 0.0f;

 M[8] = 0.0f;
 M[9] = 0.0f;
 M[10] = 1.0f;
 M[11] = 0.0f;

 M[12] = 0.0f;
 M[13] = 0.0f;
 M[14] = 0.0f;
 M[15] = 1.0f;
}