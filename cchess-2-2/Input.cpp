#include "Input.h"

using namespace space;
using namespace screen;
using namespace output;

HANDLE g_console;

Mouse g_mouse;

void InitInput()
{
    // A handle for the input stream
    g_console = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(g_console, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

Coord Mouse::MouseToBoardspace(COORD pos)
{
    PixelPos out;
    out.x = pos.X * 8;
    out.y = pos.Y * 16;
    out = out / gameScale;
    return BoardSpace(out);
}

bool Mouse::CheckMouseState()
{
    bool state = isMouseClicked;

    isMouseClicked = false;

    return state;
}

Coord Mouse::GetMouseClickCoord()
{
    return clickCoord;
}

Coord Mouse::ReadMouseHover()
{
    return tileCoord;
}

void Mouse::MouseEventProc(MOUSE_EVENT_RECORD mEvent)
{
    switch (mEvent.dwEventFlags)
    {
    case 0:
        if (mEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            isMouseClicked = true;
            clickCoord = tileCoord;
        }
        break;

    case MOUSE_MOVED:
        tileCoord = MouseToBoardspace(mEvent.dwMousePosition);
        break;

    default:
        break;
    }
}

void PingInput()
{
    DWORD eventCount = 0;

    INPUT_RECORD irec;

    while (true)
    {
        if (PeekConsoleInput(g_console, &irec, 1, &eventCount) && eventCount > 0)
        {
            ReadConsoleInput(g_console, &irec, 1, &eventCount);

            if (irec.EventType == MOUSE_EVENT) g_mouse.MouseEventProc(irec.Event.MouseEvent);
        }
        else break;
    }
}
