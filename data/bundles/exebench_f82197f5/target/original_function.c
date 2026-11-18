void UNLOCK(int *f)
{
int old;

  old = __sync_fetch_and_sub(f, 1);

  switch(old)
  {
    case 1:
    {


    }
    break;

    case 2:
    {


      old = __sync_lock_test_and_set(f, 0);


      syscall(SYS_futex, f, FUTEX_WAKE, 1);
    }
    break;

    default:
    {

    }
  }
}