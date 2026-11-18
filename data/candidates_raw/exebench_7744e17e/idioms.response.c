void get_ip(unsigned int command_ee, struct _ip *result_ee)
{
  if (command_ee > 128)
  {
    result_ee->err = 502;
    return;
  }
  result_ee->err = 0;
  result_ee->ip = (command_ee * 256) + 229376;
}