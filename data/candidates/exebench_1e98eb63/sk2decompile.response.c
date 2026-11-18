void getRange(double min, double max, double value, double *rangeMax,
              double *rangeMin) {
  if (value < max)
    *rangeMin = value;
  else
    *rangeMin = max;
  if (value > min)
    *rangeMax = value;
  else
    *rangeMax = min;
}