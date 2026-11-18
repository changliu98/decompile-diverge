int get_color(int level)
{
  int color;
  switch (level)
  {
    case 2:
    case 3:
      color = 36;
      break;
    case 4:
      color = 33;
      break;
    case 5:
      color = 32;
      break;
    case 6:
      color = 35;
      break;
    case 7:
      color = 31;
      break;
    case 8:
      color = 34;
      break;
    default:
      color = 37;
      break;
  }
  return (color);
}