int stszin(int size)
{
 int i;
 unsigned int ofs;
 unsigned int s;

 u32in();
 u32in();
 mp4config.frame.ents = u32in();

 mp4config.frame.data = malloc(sizeof(int)*(mp4config.frame.ents+1));
 if(!mp4config.frame.data)
  return -1;

 ofs = 0;
 mp4config.frame.data[0] = 0;
 for(i = 0; i < size; i++)
 {
  s = u32in();
  ofs += s;
  if(s > mp4config.frame.maxsize)
   mp4config.frame.maxsize = s;
  mp4config.frame.data[i+1] = ofs;
  if(mp4config.frame.data[i+1] < mp4config.frame.data[i])
   return -1;
 }
 return i;
}