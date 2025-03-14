// ScrollLEDs.c

#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define READ_GPIO(dir)  (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

// 延时函数
void delay(unsigned int delay_time) {
    volatile unsigned int i;
    for (i = 0; i < delay_time; i++) {
        __asm__("nop");
    }
}

// LED滚动函数
void scroll_pattern(unsigned int pattern, int direction) {
    int i;
    unsigned int display;
    
    // 向左滚动
    if (direction == 0) {
        i = 1;
        do{
            pattern = pattern << i;
            i++;
            WRITE_GPIO(GPIO_LEDs, pattern);
            delay(1000000);
        }while(pattern < 65536)
    }
    // 向右滚动
    else {
        i = 1;
        do{
            pattern = pattern >> i;
            i++;
            WRITE_GPIO(GPIO_LEDs, pattern);
            delay(1000000);
        }while((pattern & 1) == 0)
    }
}

int main(void) {
    int En_Value = 0xFFFF;
    unsigned int pattern;
    
    // 设置GPIO方向
    WRITE_GPIO(GPIO_INOUT, En_Value);

    while (1) {
        for (int i = 1; i < 16; i++)
        {
            WRITE_GPIO(GPIO_LEDs, pattern);
            delay(2000000);
            scroll_pattern(pattern, 0);  // 右到左
            scroll_pattern(pattern, 1);  // 左到右  
            delay(1000000);
            pattern += (1 << i);
        }
        
        // 全部LED熄灭，准备下一轮
        WRITE_GPIO(GPIO_LEDs, 0);
        delay(200000);
    }
    
    return 0;
}