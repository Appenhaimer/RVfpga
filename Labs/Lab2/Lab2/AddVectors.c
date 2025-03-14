#if defined(D_NEXYS_A7)
   #include <bsp_printf.h>
   #include <bsp_mem_map.h>
   #include <bsp_version.h>
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif
#include <psp_api.h>
#include <math.h>

#define N 12

int main(void){
    static int A[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    static int B[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int C[N];
    int i;
    while(1){
        for (i = 0; i < N; i++){
            C[i] = abs(A[i] + B[N-i-1]);
        }
        printfNexys("C[%d] = %d\n", i, C[i]);
    }
    return 0;
}
