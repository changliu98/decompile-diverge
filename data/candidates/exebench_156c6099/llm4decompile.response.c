void atmcpy(atm *in,atm *out)
{
  out->press = in->press;
  out->temp = in->temp;
  out->hum = in->hum;
}