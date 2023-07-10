#ifndef INPUT_H
#define INPUT_H
#include <sal.h>
#include <Windows.h>

// Keep parity with winnt.h
typedef void *HANDLE;

extern HANDLE inputHandle;

typedef struct MouseEvent {

    int x, y;
    _Bool isDown : 1;
    _Bool isDownChanged : 1; // used for "is pressed" or "is released"

} MouseEvent;

#define MOUSE_PRESSED(evnt) (evnt.isDown && evnt.isDownChanged)
#define MOUSE_RELEASED(evnt) (!evnt.isDown && evnt.isDownChanged)

MouseEvent PollMouseEvent(RECT ignoreMovementWithin);

#endif // !INPUT_H