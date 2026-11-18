void divmod(int *div, int *mod, int max)
{
  *mod += *div / max;
  *div = *div % max;
}