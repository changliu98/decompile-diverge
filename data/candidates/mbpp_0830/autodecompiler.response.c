double func0(double numToRound, int precision) {
  double div = pow(10.0, -precision);
  double tmp = ceil(numToRound / div) * div;
  double retVal = round(tmp * pow(10.0, precision)) / pow(10.0, precision);

  return retVal;
}