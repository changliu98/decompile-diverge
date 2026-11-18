int pipe2(int pipefd[2], int flags)
{
 int pfd[2];
 int err;

 if (pipe(pfd)) {
  err = (*___errno_location());
 } else {
  pipefd[0] = pfd[0];
  pipefd[1] = pfd[1];



  err = 0;
 }

 return err;
}