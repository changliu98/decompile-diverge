int my_putnbr_base(int nbr, char *base)
{
  int result;

  if (nbr < 10)
    {
      my_putchar(base[nbr]);
      return (nbr);
    }
  else
    {
      result = my_putnbr_base(nbr / 10, base);
      my_putchar(base[nbr % 10]);
      return (result);
    }
}