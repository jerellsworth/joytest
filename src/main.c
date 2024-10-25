#include <genesis.h>

u16 console_line;
u16 scroll_offset;

void print(char *buf) {
    if (console_line >= 27) {
        scroll_offset += 8;
        VDP_setVerticalScroll(BG_A, scroll_offset);
    }
    u16 bg_line = console_line % 64;
    VDP_clearText(0, bg_line, 40);
    VDP_drawText(buf, 0, bg_line);
    ++console_line;
    SYS_doVBlankProcess();
}

void print_detected_ports() {
    char buf[40];
    for (u8 pi = 0; pi < 2; ++pi) {
        sprintf(buf, "PORT_%d", pi + 1);
        print(buf);
        switch (JOY_getPortType(PORT_1 + pi)) {
            case PORT_TYPE_MENACER:
               print("PORT_TYPE_MENACER");
               break;
            case PORT_TYPE_JUSTIFIER:
               print("PORT_TYPE_JUSTIFIER");
               break;
            case PORT_TYPE_MOUSE:
               print("PORT_TYPE_MOUSE");
               break;
            case PORT_TYPE_TEAMPLAYER:
               print("PORT_TYPE_TEAMPLAYER");
               break;
            case PORT_TYPE_PAD:
               print("PORT_TYPE_PAD");
               break;
            case PORT_TYPE_UNKNOWN:
               print("PORT_TYPE_UNKNOWN");
               break;
            case PORT_TYPE_EA4WAYPLAY:
               print("PORT_TYPE_EA4WAYPLAY");
               break;
            default:
               print("unsupported port type");
               break;
        }
    }
}

int main(bool hard_reset) {
    if (!hard_reset) SYS_hardReset();

    console_line = 0;
    scroll_offset = 0;

    u16 frames = 0;
    VDP_setPlaneSize(64, 64, TRUE);
    print_detected_ports();
    while (TRUE) {
        SYS_doVBlankProcess();
        ++frames;
    }
	return 0;
}
