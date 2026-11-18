static unsigned int uniphier_gpio_irq_en(unsigned int bank)
{
 int reg = (bank * 8) + 1;
 if (reg >= (UNIPHIER_GPIO_IRQ_EN - 1))
  reg += 16;
 return reg;
}