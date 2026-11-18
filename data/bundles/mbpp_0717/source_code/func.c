#include <stdio.h>

#include <math.h>

#include <assert.h>



double avg_calc(double *ls, int len) {

    double mean = 0.0;

    if (len <= 1) {

        return ls[0];

    }

    for (int i = 0; i < len; i++) {

        mean += ls[i];

    }

    mean /= len;

    return mean;

}



double func0(double *data, int len) {
  if (len <= 1) {
    return 0.0;
  }
  double mean = avg_calc(data, len);
  double sd = 0.0;
  for (int i = 0; i < len; i++) {
    sd += (data[i] - mean) * (data[i] - mean);
  }
  sd = sqrt(sd / (len - 1));
  return sd;
}
