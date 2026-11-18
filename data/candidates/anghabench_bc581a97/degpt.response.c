double estLog(double N)
{
  // Initialize logN with a constant value (likely log of base)
  double estimatedLog = logBaseConstant;
  
  // Loop to estimate logarithm by repeatedly multiplying x by a base constant
  // until x exceeds N, incrementing logN each iteration
  for (double currentValue = baseConstant; currentValue < N; currentValue = baseConstant * currentValue) {
    // Add the constant to logN for each multiplication step
    estimatedLog = logBaseConstant + estimatedLog;
  }
  
  // Return the estimated logarithm value
  return estimatedLog;
}