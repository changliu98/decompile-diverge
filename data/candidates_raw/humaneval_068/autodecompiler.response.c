void readArray(int EV_array[], int EV_length)
{
  int EV_i;
  int EV_j;
  int EV_temp;
  struct EVPair EV_smallest;
  EV_i=0;
  while (1==1)
  {
    if (EV_i < EV_length)
    {
      EV_temp=read();
      if ((EV_temp > 0) && (EV_temp <= 1000000))
      {
        EV_array[EV_i]=EV_temp;
        EV_i=(EV_i + 1);
      }
    }
    else
    {
      EV_smallest=findSmallestEven(EV_array, EV_length, EV_smallest);
      if (EV_smallest != NULL)
      {
        printf__bench("%d %d\n", EV_smallest->EV_number, EV_smallest->EV_index);
      }
      else
      {
        printf__bench("0 0\n");
      }
      return;
    }
  }
}