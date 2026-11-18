void f_close_out(int *pipe, int *in, int *i)
{
  close(pipe[1]);
  *in = pipe[0];
  (*i)++;
}