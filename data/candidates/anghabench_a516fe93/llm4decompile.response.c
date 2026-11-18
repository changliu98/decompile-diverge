void nvgTransformTranslate(float* t, float tx, float ty)
{
 t[0] = 1.0f; t[1] = 0.0f; t[2] = 0.0f;
 t[3] = 1.0f; t[4] = tx; t[5] = ty;
}