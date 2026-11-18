void __cdecl swt_max(const double *inputSignal, int signalLength, double *maxValue)
{
  *maxValue = inputSignal[0];
  
  for (int i = 1; i < signalLength; ++i)
  {
    if (inputSignal[i] > *maxValue)
    {
      *maxValue = inputSignal[i];
    }
  }
}