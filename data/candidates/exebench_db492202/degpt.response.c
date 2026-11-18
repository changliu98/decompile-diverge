\*
// Sets the first element of the table to the calculated duration in samples
// by multiplying duration (dur) by sample rate (SR) and subtracting a constant offset (DAT_00102008)
*table = (float)(long)((double)(duration * sampleRate) - DAT_00102008);

// Sets the second element of the table to the table size minus one
table[1] = (float)(tableSize + -1);
*\ 
 
void tableset(float sampleRate,float duration,int tableSize,float *table)
{
  *table = (float)(long)((double)(duration * sampleRate) - DAT_00102008);
  table[1] = (float)(tableSize + -1);
}