int gpio_to_irq(unsigned int pin, unsigned int gpio_offset)
{
 int irq;

 switch(gpio_offset) {
 case GPIO_PIN_A:
 case GPIO_PIN_B:
  irq = 13;
  break;
 case GPIO_PIN_C:
 case GPIO_PIN_D:
 case GPIO_PIN_E:
 case GPIO_PIN_F:
 case GPIO_PIN_G:
 case GPIO_PIN_H:
 case GPIO_PIN_I:
 case GPIO_PIN_J:
  irq = 14;
  break;
 default:
  irq = 15;
 }

 return irq;
}