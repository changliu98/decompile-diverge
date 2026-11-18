float pluck(struct pluck *p, float in)
{
 float out;

 p->delay += 0.5;
 if (p->delay >= p->length) {
  p->delay = 1.0;
  out = p->buffer[p->length - 1];
  p->buffer[p->length - 1] = p->feedback * p->buffer[p->length - 2] +
   p->damping * p->buffer[p->length - 1] + in;
 } else {
  int index = (int)p->delay;
  out = p->buffer[index];
  p->buffer[index] = p->feedback * p->buffer[index - 1] +
   p->damping * p->buffer[index] + in;
 }
 return out;
}