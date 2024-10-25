#include <genesis.h>

u16 console_line;
u16 scroll_offset;

void print(char *buf) {
    if (console_line >= 27) {
        scroll_offset += 8;
        VDP_setVerticalScroll(BG_A, scroll_offset);
    }
    ++console_line;
    VDP_clearText(0, console_line, 40);
    VDP_drawText(buf, 0, console_line);
}

int main(bool hard_reset) {
    if (!hard_reset) SYS_hardReset();

    console_line = 0;
    scroll_offset = 0;

    u16 frames = 0;
    while (TRUE) {
        if (!(frames & 7)) {
            char buf[40];
            sprintf(buf, "%d", frames);
            print(buf);
        }
        SYS_doVBlankProcess();
        ++frames;
    }
	return 0;
}
