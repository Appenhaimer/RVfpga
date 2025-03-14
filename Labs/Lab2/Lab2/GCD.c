#if defined(D_NEXYS_A7)
   #include <bsp_printf.h>
   #include <bsp_mem_map.h>
   #include <bsp_version.h>
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif
#include <psp_api.h>
 
int Euclidean_GCD(int a, int b){
    int temp;
    while(b!=0){
        temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}

int main(void) {
    static int a = 48;
    static int b = 36;
    
    // Initialize UART
    uartInit();

    while(1){
        // Print the GCD of a and b
        printfNexys("%d",Euclidean_GCD(a, b)); 
    }
    return 0;
}