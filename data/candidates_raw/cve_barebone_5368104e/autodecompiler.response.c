static int
Sound_LoadSample(Stream *stream, Sample *sample)
{
 int result;

 if (((unsigned short) sample->length) > 0)
 {
  unsigned long end = sample->offset + ((unsigned short) sample->length);

  if (end > Stream_Length(stream))
  {
   result = -1;
  }
  else
  {
   sample->data = (char *) malloc(((unsigned short) sample->length));

   if (sample->data == NULL)
   {
    result = -1;
   }
   else
   {
    Stream_SetPosition(stream, sample->offset);
    Stream_Read(stream, sample->data, ((unsigned short) sample->length));
   }
  }
 }

 result = 1;

 return result;
}