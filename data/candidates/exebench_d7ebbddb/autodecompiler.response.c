void raw_relu_bulk_apply_function(int len, float *buf)
{
    int i;
    double t;

    for (i = 0; ; i++)
    {
 if (i >= len)
     break;
 t = buf[i];
 if (t > 0.0)
     t = buf[i];
 else
     t = 0.0;
 buf[i] = (float) t;
    }
}