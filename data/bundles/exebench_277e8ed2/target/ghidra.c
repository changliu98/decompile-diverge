void calc_sth11(float *p_humidity,float *p_temperature)

{
  float fVar1;
  float fVar2;
  float t_C;
  float rh_true;
  float rh_lin;
  float t;
  float rh;
  float d2;
  float d1;
  float T2;
  float T1;
  float C3;
  float C2;
  float C1;
  float *p_temperature_local;
  float *p_humidity_local;
  
  fVar1 = *p_humidity;
  fVar2 = *p_temperature * DAT_0010200c + DAT_00102020;
  rh_true = (fVar2 - DAT_00102010) * (fVar1 * DAT_00102008 + DAT_0010200c) +
            DAT_0010201c * fVar1 * fVar1 + DAT_00102018 * fVar1 + DAT_00102014;
  if (DAT_00102004 < rh_true) {
    rh_true = DAT_00102004;
  }
  if ((double)rh_true < DAT_00102028) {
    rh_true = DAT_00102024;
  }
  *p_temperature = fVar2;
  *p_humidity = rh_true;
  return;
}