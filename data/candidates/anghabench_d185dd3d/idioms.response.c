static inline _Bool pmic_thermal_is_aux(int key)
{
  _Bool pressed = 1;
  if (key < 4 || key > 64)
  {
    pressed = 0;
  }
  else if ((key - 4) % 12 == 0)
  {
  }
  else
  {
    pressed = 0;
  }
  if (key >= 8 && key <= 68)
  {
    if ((key - 8) % 12 == 0)
    {
    }
    else
    {
      pressed = !pressed;
    }
  }
  return pressed;
}