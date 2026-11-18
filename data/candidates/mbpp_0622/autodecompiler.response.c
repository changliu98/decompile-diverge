float func0(int *nums1, int *nums2, int numsSize)
{
 int m1 = -1, m2 = -1;
 int i=0, j=0, k=0;

 while(1)
 {
  if(k>=(numsSize+2)/2)
   break;
  k++;
  if(i==numsSize)
  {
   m1 = m2;
   m2 = nums2[j];
   break;
  }
  if(j==numsSize)
  {
   m1 = m2;
   m2 = nums1[i];
   break;
  }
  if(nums1[i]<=nums2[j])
  {
   m1 = m2;
   m2 = nums1[i];
   i++;
  }
  else
  {
   m1 = m2;
   m2 = nums2[j];
   j++;
  }
 }
 return ((double)(m1+m2))/2;
}