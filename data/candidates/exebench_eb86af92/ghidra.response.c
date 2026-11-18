void maxind(double *segmentToAnalyze,int length,double *maximum,double *index)

{
  int i;
  double *index_local;
  double *maximum_local;
  int length_local;
  double *segmentToAnalyze_local;
  
  *maximum = *segmentToAnalyze;
  *index = 0.0;
  for (i = 1; i < length; i = i + 1) {
    if (*maximum <= segmentToAnalyze[i] && segmentToAnalyze[i] != *maximum) {
      *maximum = segmentToAnalyze[i];
      *index = DAT_00102008 * (double)i;
    }
  }
  return;
}