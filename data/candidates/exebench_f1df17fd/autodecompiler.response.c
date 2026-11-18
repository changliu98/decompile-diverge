int FNEGQ(double *out, float *in)
{
 *(unsigned long long *) out = *(unsigned int *) &in[0] ^ (1ULL << 63);
 *(unsigned long long *) out |= (unsigned long long) in[1] << 32;
 return 1;
}