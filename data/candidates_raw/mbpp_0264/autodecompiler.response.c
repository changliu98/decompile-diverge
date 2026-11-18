double
femto (int age)
{
  double femtoseconds;

  if (age < 0)
    exit (1);

  if (age <= 2)
    femtoseconds = age * 10.5;
  else
    femtoseconds = 21 + ((age - 2) * 4);

  return femtoseconds;
}