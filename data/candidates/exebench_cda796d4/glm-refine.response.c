void __cdecl std::swap<std::__function::__policy const*>(std::__function::__policy const** p1, std::__function::__policy const** p2)
{
  std::__function::__policy const* tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}