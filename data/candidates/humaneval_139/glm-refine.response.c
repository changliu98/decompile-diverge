__int64 __cdecl func0(int n)
{
  __int64 superfactorial = 1;
  __int64 factorial = 1;

  for (int i = 1; i <= n; ++i)
  {
    factorial *= i;        // Calculates i! (1, 2, 6, 24, ...)
    superfactorial *= factorial; // Multiplies the current factorial into the total product
  }

  return superfactorial;
}