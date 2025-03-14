// memory-mapped I/O addresses
#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir)  (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }


int main(void) {
    int En_Value = 0xFFFF;  // 使能值
    unsigned int switches_value_low;
    unsigned int switches_value_high;
    
    // 设置GPIO方向，LED设为输出
    WRITE_GPIO(GPIO_INOUT, En_Value);
    
    while (1) {
        // 读取开关值
        switches_value_low = (READ_GPIO(GPIO_SWs)>>16)&(0x0000000F);
        switches_value_high = ((READ_GPIO(GPIO_SWs)>>16)&(0x0000F000))>>12;

        // 显示开关值到LED，当发生无符号溢出（即进位为1）时，LED的第五位应亮起
        if (switches_value_low + switches_value_high >> 15) {
            WRITE_GPIO(GPIO_LEDs, 0x00000020);
        } else {
            WRITE_GPIO(GPIO_LEDs, switches_value_low + switches_value_high);
        }

    }
    
    return 0;
}