#if defined(D_NEXYS_A7)
   #include <bsp_printf.h>
   #include <bsp_mem_map.h>
   #include <bsp_version.h>
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif
#include <psp_api.h>

#define MAX_FIB 12
int Fib[MAX_FIB];

int Fibonacci(int n){
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;
    //storage
    if (Fib[n] != 0) return Fib[n];
    Fib[n] = Fibonacci(n-1) + Fibonacci(n-2);
    return Fib[n];
}

int main(void){
    int i;
    while(1){
        for (i = 0; i < MAX_FIB; i++){
            printfNexys("Fib[%d] = %d\n", i, Fibonacci(i));
        }
    }
    return 0;
}
