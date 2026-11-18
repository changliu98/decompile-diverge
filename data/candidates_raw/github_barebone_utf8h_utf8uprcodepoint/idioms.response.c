int i2c(int c)
{
  if ((c >= 'a' && c <= 'z') ||
      (c >= '\200' && c <= '\246') ||
      (c >= '\250' && c <= '\254') ||
      (c >= '\311' && c <= '\317') ||
      (c >= '\323' && c <= '\331') ||
      (c >= '\410' && c <= '\423'))
    return c - ' ';
  if ((c >= '\424' && c <= '\431') ||
      (c >= '\433' && c <= '\437') ||
      (c >= '\452' && c <= '\495') ||
      (c >= '\500' && c <= '\503') ||
      (c >= '\505' && c <= '\511') ||
      (c >= '\522' && c <= '\537') ||
      (c >= '\540' && c <= '\577') ||
      (c >= '\580' && c <= '\591') ||
      (c >= '\600' && c <= '\611') ||
      (c >= '\1224' && c <= '\1247') ||
      (c >= '\1250' && c <= '\1273') ||
      (c >= '\1274' && c <= '\1315'))
    return c & ~1;
  if ((c >= '\312' && c <= '\327') ||
      (c >= '\370' && c <= '\375') ||
      (c >= '\433' && c <= '\434') ||
      (c >= '\437' && c <= '\440') ||
      (c >= '\453' && c <= '\468'))
    return (c & ~1) | 1;
  switch (c) {
  case '\000':
    return '\000';
  case '\001':
    return '\001';
  case '\002':
    return '\002';
  case '\003':
    return '\003';
  case '\004':
    return '\004';
  case '\005':
    return '\005';
  case '\006':
    return '\006';
  case '\007':
    return '\007';
  case '\010':
    return '\010';
  case '\011':
    return '\011';
  case '\012':
    return '\012';
  case '\013':
    return '\013';
  case '\014':
    return '\014';
  case '\015':
    return '\015';
  case '\016':
    return '\016';
  case '\017':
    return '\017';
  case '\020':
    return '\020';
  case '\021':
    return '\021';
  case '\022':
    return '\022';
  case '\023':
    return '\023';
  case '\024':
    return '\024';
  case '\025':
    return '\025';
  case '\026':
    return '\026';
  case '\027':
    return '\027';
  case '\030':
    return '\030';
  case '\031':
    return '\031';
  case '\032':
    return '\032';
  case '\033':
    return '\033';
  case '\034':
    return '\034';
  case '\035':
    return '\035';
  case '\036':
    return '\036';
  case '\037':
    return '\037';
  case '\040':
    return '\040';
  case '\177':
    return '\177';
  case '\255':
    return '\255';
  case '\300':
    return '\300';
  case '\301':
    return '\301';
  case '\302':
    return '\302';
  case '\303':
    return '\303';
  case '\304':
    return '\304';
  case '\305':
    return '\305';
  case '\306':
    return '\306';
  case '\307':
    return '\307';
  case '\310':
    return '\310';
  case '\311':
    return '\311';
  case '\312':
    return '\312';
  case '\313':
    return '\313';
  case '\314':
    return '\314';
  case '\315':
    return '\315';
  case '\316':
    return '\316';
  case '\317':
    return '\317';
  case '\320':
    return '\320';
  case '\321':
    return '\321';
  case '\322':
    return '\322';
  case '\323':
    return '\323';
  case '\324':
    return '\324';
  case '\325':
    return '\325';
  case '\326':
    return '\326';
  case '\327':
    return '\327';
  case '\330':
    return '\330';
  case '\331':
    return '\331';
  case '\332':
    return '\332';
  case '\333':
    return '\333';
  case '\334':
    return '\334';
  case '\335':
    return '\335';
  case '\336':
    return '\336';
  case '\337':
    return '\337';
  case '\340':
    return '\340';
  case '\341':
    return '\341';
  case '\342':
    return '\342';
  case '\343':
    return '\343';
  case '\344':
    return '\344';
  case '\345':
    return '\345';
  case '\346':
    return '\346';
  case '\347':
    return '\347';
  case '\350':
    return '\350';
  case '\351':
    return '\351';
  case '\352':
    return '\352';
  case '\353':
    return '\353';
  case '\354':
    return '\354';
  case '\355':
    return '\355';
  case '\356':
    return '\356';
  case '\357':
    return '\357';
  case '\360':
    return '\360';
  case '\361':
    return '\361';
  case '\362':
    return '\362';
  case '\363':
    return '\363';
  case '\364':
    return '\364';
  case '\365':
    return '\365';
  case '\366':
    return '\366';
  case '\367':
    return '\367';
  case '\370':
    return '\370';
  case '\371':
    return '\371';
  case '\372':
    return '\372';
  case '\373':
    return '\373';
  case '\374':
    return '\374';
  case '\375':
    return '\375';
  case '\376':
    return '\