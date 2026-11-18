int shape_tria3(triode_t *triode, double *voltages)
{
 voltages[0] = triode->vg;
 voltages[1] = triode->vk;
 voltages[2] = 1.0 - triode->vg - triode->vk;

 return 0;
}