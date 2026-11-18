double HTS_rnd(HTS_Rand * rand)
{
   *rand = (HTS_Rand) (((HTS_Rand) 1103515245) * *rand + (HTS_Rand) 12345);
   return (double) ((*rand >> 16) & 0x7fff) / (double) 0x8000;
}