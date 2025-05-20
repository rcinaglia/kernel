#include "vga.h"

void kmain()
{
    fb_write("test vga text driver", COLOR_WHITE, COLOR_BLACK);
}
