/*

https://www.redhat.com/en/blog/fighting-exploits-control-flow-integrity-cfi-clang

clang buffer_overflow_cfi.cpp
perl -e 'print "a"x8 .  "\x50\x11\x40"' | ./a.out

clang buffer_overflow_cfi.cpp -flto -fsanitize=cfi -fvisibility=default
perl -e 'print "a"x8 .  "\x50\x11\x40"' | ./a.out

*/


#include <stdio.h>
#include <string.h>

#define AUTHMAX 4

struct auth {
  char pass[AUTHMAX];
  void (*func)(struct auth *);
};

void success(struct auth*) { printf("Authenticated successfully\n"); }

void failure(struct auth*) { printf("Authentication failed\n"); }

void auth(struct auth *a) {
  if (strcmp(a->pass, "pass") == 0)
    a->func = &success;
  else
    a->func = &failure;
  a->func++;
}

int main(int argc, char **argv) {
  struct auth a;

  a.func = &auth;

  printf("Enter your password:\n");
  scanf("%s", &a.pass);

  a.func(&a);
}