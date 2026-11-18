void sios_ntohll(char *str, unsigned int *ll)
{
  *ll = (str[0] << 24) + (str[1] << 16) + (str[2] << 8) + str[3];
}