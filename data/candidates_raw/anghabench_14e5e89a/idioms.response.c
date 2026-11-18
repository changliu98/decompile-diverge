static inline unsigned int rta_getattr_u32(unsigned char *rta, unsigned int rta_type)
{
 return ((unsigned int *) (rta)) [((rta_type) / sizeof(unsigned int))];
}