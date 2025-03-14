#if defined(D_NEXYS_A7)
   #include <bsp_printf.h>
   #include <bsp_mem_map.h>
   #include <bsp_version.h>
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif
#include <psp_api.h>

#define N 12

int main(void){
    int list[N] = {0,1,2,7,-8,4,5,12,11,-2,6,3};
    int i, temp, flag;
    uartInit();
    do{
        flag = 0;
        for (i = 0; i < N-1; i++){
            if (list[i] > list[i+1]){
                temp = list[i];
                list[i] = list[i+1];
                list[i+1] = temp;
                flag = 1;
            }
        }
    }while(flag);
    printfNexys("The sorted list is: ");
    for (i = 0; i < N; i++){
        printfNexys("%d ", list[i]);
    }
    return 0;
}


