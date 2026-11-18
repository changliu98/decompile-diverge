static int get_pin_group(int pin, int gpio_offset)
{
  int group = -1;
  switch (gpio_offset) {
  case 0x84:
  case 0x87:
    group = 13;
    break;
  case 0x80:
  case 0x81:
  case 0x82:
  case 0x83:
  case 0x85:
  case 0x86:
  case 0x88:
  case 0x89:
  case 0x8A:
  case 0x8B:
  case 0x8C:
  case 0x8D:
  case 0x8E:
  case 0x8F:
    group = 14;
    break;
  case 0x7C:
  case 0x7D:
  case 0x7E:
  case 0x7F:
    group = 15;
    break;
  default:
    break;
  }
  return group;
}