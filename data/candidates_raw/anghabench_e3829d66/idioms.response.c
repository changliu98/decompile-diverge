double srgb2xyz(double white, double *buf)
{
  double blue;
  buf[0] = (buf[0] * 0.0555179) + (buf[0] * -0.99886);
  buf[1] = (buf[1] * 0.0750759) + (buf[1] * -0.99332);
  buf[2] = (buf[2] * 0.153852 ) + (buf[2] * -0.969);
  buf[3] = (buf[3] * 0.3104856) + (buf[3] * -0.8665);
  buf[4] = (buf[4] * 0.5329522) + (buf[4] * -0.55);
  buf[5] = (buf[5] * -0.016898) + (buf[5] * 0.7616);
  blue = (buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6] + (buf[6] * 0.5362));
  buf[6] = (buf[6] * 0.115926);
  return (blue * 0.11);
}