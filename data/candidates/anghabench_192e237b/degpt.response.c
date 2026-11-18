double estLog(double N)
{
  // Initialize logN with a constant value from DAT_00102010
  double estimatedLog = DAT_00102010;
  // Iterate x starting from DAT_00102008, doubling x each iteration until x >= N
  for (double currentValue = DAT_00102008; currentValue < N; currentValue = DAT_00102008 * currentValue) {
    // Update logN by adding the constant value from DAT_00102010
    estimatedLog = DAT_00102010 + estimatedLog;
  }
  // Return the estimated logarithm value
  return estimatedLog;
}