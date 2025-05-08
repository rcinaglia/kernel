/** vga.c
 *  Driver VGA Text Mode
 *
 *  PROX. Graphics Mod e
 */

#include "vga.h"
#include "io.h"

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, VGA_COLOR fg, VGA_COLOR bg) {
    if(i!=0)
        i = i*2;
    char *fb = (char *) 0x000B8000;
    fb[i] = c;
    fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}


static unsigned short cursor_pos = 0;

#define FB_WIDTH 80
#define FB_HEIGHT 25


// minimal strlen() implementation
int strlen(char *str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void fb_write(char* buf, VGA_COLOR fg_color, VGA_COLOR bg_color)
{
    for(int i = 0; i < strlen(buf); i++)
    {
        if (buf[i] == '\n') {
            cursor_pos = (cursor_pos / FB_WIDTH + 1) * FB_WIDTH;
        }
        else {
            fb_write_cell(cursor_pos, buf[i], fg_color, bg_color);
            cursor_pos++;
        }

        fb_move_cursor(cursor_pos);
    }
}
