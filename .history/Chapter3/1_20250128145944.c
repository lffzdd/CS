typedef struct
{
  /* data */
  int a[2];
  double d;
} struct_t;

double fun(int i){
  volatile struct_t s;
  s.d=3.14;
  
}