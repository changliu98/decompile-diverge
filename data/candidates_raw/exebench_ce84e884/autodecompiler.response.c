void compute(struct In *input, struct Out *output, struct Private *priv) {
  int i;
  for(i=0; i<4; ++i) {
    output->out[i] = (input->in[i] - priv->priv[i])/2;
  }
}