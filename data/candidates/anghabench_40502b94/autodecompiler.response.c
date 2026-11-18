int
cpu_map__id_to_cpu(int v)
{
 return v & 0xffff;
}