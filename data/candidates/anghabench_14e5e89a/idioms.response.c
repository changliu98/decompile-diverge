static inline unsigned int REG_A4XX_VSC_PIPE_DATA_ADDRESS_REG(unsigned char *rta, unsigned int rta_type)
{
 return ((unsigned int *) (rta)) [((rta_type) / sizeof(unsigned int))];
}