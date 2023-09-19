/*
clang++ asan_init_order_1.cpp asan_init_order_2.cpp
./a.out 
clang++ asan_init_order_2.cpp asan_init_order_1.cpp
./a.out
*/

#include <stdio.h>
extern int extern_global;
int __attribute__((noinline)) read_extern_global() { return extern_global; }
int x = read_extern_global() + 1;
int main() {
  printf("%d\n", x);
  return 0;
}
