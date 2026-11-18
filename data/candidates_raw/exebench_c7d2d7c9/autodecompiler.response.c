void LzmaDec_InitDicAndState(CLzmaDec *p, BoolInt initDic, BoolInt initState)
{
  p->needFlush = 4;
  p->needFlush <<= 2;
}