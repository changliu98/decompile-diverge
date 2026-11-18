Optimized for reverse engineering
void __cdecl addvectors2(float *result, const float *vec, const float *vec2)
{
    result[0] = vec[0] + vec2[0];
    result[1] = vec[1] + vec2[1];
}