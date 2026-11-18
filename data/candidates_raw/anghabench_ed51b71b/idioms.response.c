int get_usb_time(int usb_rate)
{
  return (usb_rate * 125 + 512) / 1024;
}