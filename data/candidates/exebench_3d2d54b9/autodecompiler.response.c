static int foo(int xpath_token, struct xpath_res *res) {
 if (xpath_token != 9)
  res->is_valid = 0;
 else
  res->is_absolute = 0;

 return 3;
}