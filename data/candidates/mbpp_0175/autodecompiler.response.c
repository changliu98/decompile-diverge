int func0() {
 char s[100];
 scanf__bench("%s", s);

 int b = is_balanced(s);

 printf__bench("%s\n", b ? "YES" : "NO");

 return 0;
}