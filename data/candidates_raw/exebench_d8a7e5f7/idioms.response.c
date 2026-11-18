int get_nick(char *nick, char *msg)
{
  int i = 0;
  if (msg[0] == ':')
    msg++;
  for (;;) {
    int is_end = 0;
    if (msg[0] == '!')
      is_end = 1;
    else if (msg[0] == '\0')
      is_end = 1;
    if (is_end)
      break;
    nick[i] = msg[0];
    i++;
    msg++;
  }
  nick[i] = '\0';
  if (nick[0] < '0')
    return 0;
  return 1;
}