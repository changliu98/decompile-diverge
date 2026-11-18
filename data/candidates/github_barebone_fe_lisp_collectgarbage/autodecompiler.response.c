void collectgarbage(FENSTER *f)
{
 int i;
 struct mouse e_mouse;

 for (i = 0; i < f->mxedt; i++)
  fe_mark(f, f->f[i].b);
 fe_mark(f, f->fb);

 for (i = 0; i < f->mxedt + 3; i++)
 {
  struct EDIT *e = &f->e[i];

  if (((e->ins) & 1))
  {
   int mode = ((e->ins) >> 2);

   if (mode == 1)
    continue;
   else if (mode == 10 && f->save)
    (*f->save)(f, e);
   e->ins = 5;
   e->mark = f->mark;
   f->mark = e;
  }
  else
   e->ins &= ~2;
 }
}