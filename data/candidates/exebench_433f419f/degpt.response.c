void subtractvectors(float *output, float *vector1, float *vector2)
{
    // Subtract the first component of vec2 from vec and store in result
    *output = *vector1 - *vector2;
    // Subtract the second component of vec2 from vec and store in result
    output[1] = vector1[1] - vector2[1];
    // Subtract the third component of vec2 from vec and store in result
    output[2] = vector1[2] - vector2[2];
}