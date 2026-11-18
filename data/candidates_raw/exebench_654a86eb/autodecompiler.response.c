void FreePage(int pageno, struct file *f)
{
 if(f->freecount == 0)
 {
  return;
 }
 f->freecount--;
}