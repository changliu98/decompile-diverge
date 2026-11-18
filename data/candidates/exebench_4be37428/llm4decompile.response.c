void sseround(float *vec)
{
    vec[0] = (float)(((int)(vec[0] * sseround::rounders[0])) * sseround::rounders[0]);
    vec[1] = (float)(((int)(vec[1] * sseround::rounders[1])) * sseround::rounders[1]);
    vec[2] = (float)(((int)(vec[2] * sseround::rounders[2])) * sseround::rounders[2]);
    vec[3] = (float)(((int)(vec[3] * sseround::rounders[3])) * sseround::rounders[3]);
}