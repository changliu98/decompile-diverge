struct _weights *weights_new(unsigned long number_threads, unsigned long width, unsigned long height)
{
  struct _weights *weights = ((void *)0);
  for (unsigned long i = 0; i < number_threads + 1; i++)
    if ((weights = weights_resize(weights, i, number_threads + 1)) == ((void *)0))
      return ((void *)0);
  for (unsigned long i = 0; i < number_threads + 1; i++)
    if ((weights->data[i] = weights_data_new(width, height)) == ((void *)0))
      return weights_free(weights);
  return weights;
}