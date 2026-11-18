void sios_set_iovec_len(struct iovec *iov)
{
  iov->iov_len = iov->iov_len - 128;
}