#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]);
  
  for (int i = 0; i < 1000000; i++){
    /* code */
    printf("%d\r\n",i);
  }

  return 0;
}
