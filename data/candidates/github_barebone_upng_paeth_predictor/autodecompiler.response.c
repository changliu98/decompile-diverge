int paeth_predictor(int first, int middle, int last)
{
 int min, max, median;

 int sum = first + middle - last;
 if (sum > first) {
  min = first;
  max = sum - first;
 } else {
  min = sum;
  max = first;
 }

 int diff1 = (sum > middle) ? (sum - middle) : (middle - sum);
 int diff2 = (sum > last) ? (sum - last) : (last - sum);

 if (diff1 <= diff2 && diff1 <= diff2) {
  median = first;
 } else if (diff2 <= diff1 && diff2 <= diff1) {
  median = last;
 } else {
  median = sum;
 }
 return median;
}