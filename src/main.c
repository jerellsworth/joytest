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
        sprintf(buf, "Detected: PORT_%d", pi + 1);
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

void cb(u16 joy, u16 changed, u16 state) {
    char buf[40];
    sprintf(buf, "Changed: JOY_%d", joy - JOY_1 + 1);
    print(buf);
    switch (changed) {
        case BUTTON_UP:
            print("BUTTON_UP");
            break;
        case BUTTON_DOWN:
            print("BUTTON_DOWN");
            break;
        case BUTTON_LEFT:
            print("BUTTON_LEFT");
            break;
        case BUTTON_RIGHT:
            print("BUTTON_RIGHT");
            break;
        case BUTTON_A:
            print("BUTTON_A");
            break;
        case BUTTON_B:
            print("BUTTON_B");
            break;
        case BUTTON_C:
            print("BUTTON_C");
            break;
        case BUTTON_START:
            print("BUTTON_START");
            break;
        case BUTTON_X:
            print("BUTTON_X");
            break;
        case BUTTON_Y:
            print("BUTTON_Y");
            break;
        case BUTTON_Z:
            print("BUTTON_Z");
            break;
        case BUTTON_MODE:
            print("BUTTON_MODE");
            break;
        default:
            print("unknown button");
            break;
    }
    if (changed & state) {
        print("pressed");
    } else {
        print("released");
    }
}

void print_detected_joypads() {
    char buf[40];
    for (u8 ji = 0; ji < 8; ++ji) {
        sprintf(buf, "Detected: JOY_%d", ji + 1);
        print(buf);
        switch (JOY_getJoypadType(JOY_1 + ji)) {
            case JOY_TYPE_PAD3:
               print("JOY_TYPE_PAD3");
               break;
            case JOY_TYPE_PAD6:
               print("JOY_TYPE_PAD6");
               break;
            case JOY_TYPE_MOUSE:
               print("JOY_TYPE_MOUSE");
               break;
            case JOY_TYPE_TRACKBALL:
               print("JOY_TYPE_TRACKBALL");
               break;
            case JOY_TYPE_MENACER:
               print("JOY_TYPE_MENACER");
               break;
            case JOY_TYPE_JUSTIFIER:
               print("JOY_TYPE_JUSTIFIER");
               break;
            case JOY_TYPE_UNKNOWN:
               print("JOY_TYPE_UNKNOWN");
               break;
            default:
               print("unsupported joy pad type");
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
    print_detected_joypads();
    JOY_setEventHandler(&cb);
    while (TRUE) {
        SYS_doVBlankProcess();
        ++frames;
    }
	return 0;
}
