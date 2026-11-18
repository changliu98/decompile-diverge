unsigned int __cdecl uniphier_gpio_bank_to_reg(unsigned int bank)
{
  unsigned int reg; // [rsp+0h] [rbp-8h]

  reg = 8 * (bank + 1);
  if ( reg >= UNIPHIER_GPIO_IRQ_EN )
    reg += 16;
  return reg;
}