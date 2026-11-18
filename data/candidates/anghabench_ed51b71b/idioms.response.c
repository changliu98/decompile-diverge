int get_high_speed_hz(int usb_rate)
{
  return (usb_rate * 125 + 512) / 1024;
}