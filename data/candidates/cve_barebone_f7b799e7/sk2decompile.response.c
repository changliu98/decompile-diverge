static void color_cmyk_to_rgb(gx_device_printer *pdev) {
  unsigned int width = pdev->color_comp[0].width;
  unsigned int height = pdev->color_comp[0].height;
  unsigned int i;
  float c_scale, m_scale, y_scale, k_scale;
  float r, g, b, k;
  if (pdev->num_color_comp < 4) {
    return;
  }
  c_scale = 1.0f / ((1 << pdev->color_comp[0].depth) - 1);
  m_scale = 1.0f / ((1 << pdev->color_comp[1].depth) - 1);
  y_scale = 1.0f / ((1 << pdev->color_comp[2].depth) - 1);
  k_scale = 1.0f / ((1 << pdev->color_comp[3].depth) - 1);
  for (i = 0; i < width * height; i++) {
    r = 1.0f - c_scale * pdev->color_comp[0].data[i];
    g = 1.0f - m_scale * pdev->color_comp[1].data[i];
    b = 1.0f - y_scale * pdev->color_comp[2].data[i];
    k = 1.0f - k_scale * pdev->color_comp[3].data[i];
    pdev->color_comp[0].data[i] = (unsigned int)(255.0f * r * k);
    pdev->color_comp[1].data[i] = (unsigned int)(255.0f * g * k);
    pdev->color_comp[2].data[i] = (unsigned int)(255.0f * b * k);
  }
  free(pdev->color_comp[3].data);
  pdev->color_comp[3].data = NULL;
  pdev->color_comp[0].depth = 8;
  pdev->color_comp[1].depth = 8;
  pdev->color_comp[2].depth = 8;
  pdev->num_color_comp--;
  pdev->color_space = gs_color_space_index_RGB;
  for (i = 3; i < pdev->num_color_comp; i++) {
    pdev->color_comp[i] = pdev->color_comp[i + 1];
  }
}