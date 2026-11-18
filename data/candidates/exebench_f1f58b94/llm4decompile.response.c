void sort4_sorting_network_simple_swap(unsigned short *a)
{







  unsigned short t;
  ((a[0])<(a[1])?t=a[0],a[0]=a[1],a[1]=t:t=a[1],a[1]=a[0],a[0]=t);
  ((a[2])<(a[3])?t=a[2],a[2]=a[3],a[3]=t:t=a[3],a[3]=a[2],a[2]=t);
  ((a[0])<(a[2])?t=a[0],a[0]=a[2],a[2]=t:t=a[2],a[2]=a[0],a[0]=t);
  ((a[1])<(a[3])?t=a[1],a[1]=a[3],a[3]=t:t=a[3],a[3]=a[1],a[1]=t);
  ((a[1])<(a[2])?t=a[1],a[1]=a[2],a[2]=t:t=a[2],a[2]=a[1],a[1]=t);

}