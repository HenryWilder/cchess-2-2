#include "input.h"
#include <Windows.h>

#define NUM_CONSOLE_COL_PIXELS 8
#define NUM_CONSOLE_ROW_PIXELS 16

HANDLE inputHandle;

_Bool isDownPrev = 0;

MouseEvent PollMouseEvent(RECT ignoreMovementWithin)
{
    MOUSE_EVENT_RECORD mEvent = {0};

    int x = 0;
    int y = 0;
    _Bool isDown = 0;
    _Bool isDownChanged = 0;

    while (1)
    {
        DWORD eventCount = 0;
        INPUT_RECORD record = {0};

        _Bool isInputRecorded = PeekConsoleInput(inputHandle, &record, 1, &eventCount);
        _Bool isEventCounted  = eventCount != 0;

        if (!isInputRecorded || !isEventCounted)
        {
            continue;
        }

        (void)ReadConsoleInput(inputHandle, &record, 1, &eventCount);
        _Bool isMouseEvent = record.EventType == MOUSE_EVENT;

        if (!isMouseEvent)
        {
            continue;
        }

        mEvent = record.Event.MouseEvent;
        x = mEvent.dwMousePosition.X * NUM_CONSOLE_COL_PIXELS;
        y = mEvent.dwMousePosition.Y * NUM_CONSOLE_ROW_PIXELS;

        isDown = mEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED;
        isDownChanged = isDown != isDownPrev;
        isDownPrev = isDown;

        if (isDownChanged)
        {
            break;
        }

        POINT pt = { x, y };
        _Bool isMoveIgnored = PtInRect(&ignoreMovementWithin, pt);

        if (!isMoveIgnored)
        {
            break;
        }
    }

    MouseEvent e = {
        .x = x,
        .y = y,
        .isDown = isDown,
        .isDownChanged = isDownChanged,
    };

    return e;
}
