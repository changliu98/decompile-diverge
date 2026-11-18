short interpolate(sonicStream stream,short *in,int oldSampleRate,int newSampleRate)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int overflowCount;
  int oldSign;
  int value;
  int weight;
  int width;
  int ratio;
  int rightPosition;
  int leftPosition;
  int position;
  int total;
  int i;
  int newSampleRate_local;
  int oldSampleRate_local;
  short *in_local;
  sonicStream stream_local;
  short local_a;
  
  total = 0;
  iVar2 = stream->newRatePosition;
  iVar3 = stream->oldRatePosition;
  iVar4 = (stream->oldRatePosition + 1) * newSampleRate;
  overflowCount = 0;
  for (i = 0; i < 0xc; i = i + 1) {
    iVar5 = findSincCoefficient(i,(iVar4 - iVar2 * oldSampleRate) + -1,iVar4 - iVar3 * newSampleRate
                               );
    sVar1 = in[i * stream->numChannels];
    iVar6 = getSign(total);
    total = sVar1 * iVar5 + total;
    iVar7 = getSign(total);
    if (iVar6 != iVar7) {
      iVar5 = getSign(sVar1 * iVar5);
      if (iVar5 == iVar6) {
        overflowCount = iVar6 + overflowCount;
      }
    }
  }
  if (overflowCount < 1) {
    if (overflowCount < 0) {
      local_a = -0x8000;
    }
    else {
      local_a = (short)((uint)total >> 0x10);
    }
  }
  else {
    local_a = 0x7fff;
  }
  return local_a;
}