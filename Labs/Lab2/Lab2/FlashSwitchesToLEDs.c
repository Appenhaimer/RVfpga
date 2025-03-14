// FlashSwitchesToLEDs.c

// memory-mapped I/O addresses
#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir)  (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

// 简单的延时函数
void delay(void) {
    volatile unsigned int i;
    for (i = 0; i < 5000000; i++) {  // 可以调整此数值来改变闪烁速度
        __asm__("nop");
    }
}

int main(void) {
    int En_Value = 0xFFFF;  // 使能值
    unsigned int switches_value;
    
    // 设置GPIO方向，LED设为输出
    WRITE_GPIO(GPIO_INOUT, En_Value);
    
    while (1) {
        // 读取开关值
        switches_value = READ_GPIO(GPIO_SWs);
        // 右移16位得到实际开关值
        switches_value = switches_value >> 16;
        
        // 显示开关值到LED
        WRITE_GPIO(GPIO_LEDs, switches_value);
        delay();  // 延时
        
        // 关闭所有LED
        WRITE_GPIO(GPIO_LEDs, 0);
        delay();  // 延时
    }
    
    return 0;
}