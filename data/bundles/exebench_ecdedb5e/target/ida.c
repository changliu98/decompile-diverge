int __cdecl read_double(int fd, double *out)
{
  int err; // [rsp+4h] [rbp-1Ch]
  double d; // [rsp+8h] [rbp-18h] BYREF
  double *outa; // [rsp+10h] [rbp-10h]
  int fda; // [rsp+1Ch] [rbp-4h]

  fda = fd;
  outa = out;
  err = read(fd, &d, 8uLL);
  *outa = d;
  return err;
}