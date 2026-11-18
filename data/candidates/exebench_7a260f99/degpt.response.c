void subtractvectors2(float *output, float *vector1, float *vector2)
{
    // Subtract the first element of vec2 from vec and store in result
    *output = *vector1 - *vector2;
    // Subtract the second element of vec2 from vec and store in result[1]
    output[1] = vector1[1] - vector2[1];
}