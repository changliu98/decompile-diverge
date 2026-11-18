void tableset(float SR,float dur,int size,float *tab)

{
  float *tab_local;
  int size_local;
  float dur_local;
  float SR_local;
  
  *tab = (float)(long)((double)(dur * SR) - DAT_00102008);
  tab[1] = (float)(size + -1);
  return;
}