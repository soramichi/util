#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
  int n;
  int remaining_threads;
} arg_t;

unsigned long _fib(int n){
  if(n < 2)
    return 1;
  else
    return _fib(n-1) + _fib(n-2);
}

void* fib(void* _arg){
  int n = ((arg_t*)_arg)->n;
  int remaining_threads = ((arg_t*)_arg)->remaining_threads;
  unsigned long* retval = (unsigned long*)malloc(sizeof(unsigned long));
  
  if(n < 2){
    *retval = 1;
  }
  else{
    if(remaining_threads <= 1){
      *retval = _fib(n-1) + _fib(n-2);
    }
    else /* if(remaining_thread > 2) */{
      pthread_t pt1, pt2;
      arg_t arg_n_1 = { .n = n-1, .remaining_threads = remaining_threads/2 };
      arg_t arg_n_2 = { .n = n-2, .remaining_threads = remaining_threads/2 };
      pthread_create(&pt1, NULL, fib, &arg_n_1);
      pthread_create(&pt2, NULL, fib, &arg_n_2);

      void *getval1, *getval2;
      pthread_join(pt1, &getval1);
      pthread_join(pt2, &getval2);
      unsigned long fib_n_1 = *((unsigned long*)getval1);
      unsigned long fib_n_2 = *((unsigned long*)getval2);
      free(getval1);
      free(getval2);
      
      *retval = fib_n_1 + fib_n_2;
    }
  }

  return (void*)retval;
}

main(int argc, char* argv[]){
  int n, threads;
  unsigned long* ret;
  
  if(argc < 3){
    fprintf(stderr, "usage: %s n threads\n", argv[0]);
    exit(1);
  }
  else{
    n = atoi(argv[1]);
    threads = atoi(argv[2]);
  }

  arg_t arg = { .n = n, .remaining_threads = threads };
  ret = fib(&arg);
  printf("fib(%d) = %lu\n", n, *ret);
}
