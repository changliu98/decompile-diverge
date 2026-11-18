void Vector_Cross_Product( vec3_t out, vec3_t in1, vec3_t in2 )
{
 out[0] = in1[1]*in2[2] - in1[2]*in2[1];
 out[1] = in1[2]*in2[0] - in1[0]*in2[2];
 out[2] = in1[0]*in2[1] - in1[1]*in2[0];
}