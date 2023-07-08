# Order of dependencies

Headers will not be included until they are absolutely needed, with the exception of external libraries.

If a header only references identifiers without using them, they will be forward declared instead of including the related header.

---

### Utils.h

#### Takes

| From      | Namespace | Identifier            |
| --------- | :-------: | --------------------- |
| Windows.h |           | `HWND`                |
| Windows.h |           | `HDC`                 |
| concepts  |   `std`   | `is_integral_v`       |
| concepts  |   `std`   | `is_floating_point_v` |
| concepts  |   `std`   | `integral`            |
| concepts  |   `std`   | `floating_point`      |

#### Gives

| Namespace | Identifier     |   Kind    |
| :-------: | -------------- | :-------: |
|           | `numeric`      |  concept  |
|           | `evalable`     |  concept  |
|           | `SleepForMS()` | function  |
|           | `space`        | namespace |
|  `space`  | `game`         | namespace |
|  `space`  | `screen`       | namespace |
| `screen`  | `output`       | namespace |
|           | `IsOdd()`      | function  |
|           | `IsEven()`     | function  |
|           | `Snap()`       | function  |
|           | `Vec2`         |  struct   |
|           | `Coord`        |  struct   |
|           | `PixelPos()`   | function  |
|           | `ValidPos()`   | function  |
|           | `PixelSpace()` | function  |
|           | `BoardSpace()` | function  |
|           | `BoardTile`    |  struct   |

---

### Rendering.h

#### Takes

| From      | Namespace | Identifier |
| --------- | :-------: | ---------- |
| Windows.h |           | `COLORREF` |
| Windows.h |           | `UINT`     |
| Utils.h   |           | `Coord`    |

#### Gives

|   Namespace   | Identifier                    |   Kind    |
| :-----------: | ----------------------------- | :-------: |
|               | `Color`                       |  struct   |
|               | `CRef()`                      | function  |
|               | `sprite`                      | namespace |
|   `sprite`    | `Pltt`                        |   enum    |
|   `sprite`    | `colorPalette[]`              |   array   |
|   `sprite`    | `PaletteColor()`              | function  |
|   `sprite`    | `Sprite`                      |  struct   |
|   `sprite`    | `unit`                        | namespace |
|   `sprite`    | `symbol`                      | namespace |
|               | `frameBuffer`                 | namespace |
| `frameBuffer` | `Index`                       | function  |
| `frameBuffer` | `IsValidPxPosition`           | function  |
| `frameBuffer` | `Get`                         | function  |
| `frameBuffer` | `SpacePatternAtPos`           | function  |
| `frameBuffer` | `DrawPixel`                   | function  |
| `frameBuffer` | `DrawPixelSafe`               | function  |
| `frameBuffer` | `DrawToBufferAndScreen`       | function  |
| `frameBuffer` | `WriteToBuffer`               | function  |
| `frameBuffer` | `DrawToBufferSafe`            | function  |
| `frameBuffer` | `DrawSpriteNOW`               | function  |
| `frameBuffer` | `DrawSymbolSkippingBuffer`    | function  |
| `frameBuffer` | `DrawSpriteWithBackgroundNOW` | function  |
| `frameBuffer` | `BufferCleanplateSpace`       | function  |
| `frameBuffer` | `DrawGhost`                   | function  |
| `frameBuffer` | `DrawSprite`                  | function  |
| `frameBuffer` | `DrawRectNOW`                 | function  |
| `frameBuffer` | `DrawRect`                    | function  |
| `frameBuffer` | `DrawGridSpaceNOW`            | function  |
| `frameBuffer` | `DrawGridSpace`               | function  |
| `frameBuffer` | `DrawBoardPattern1SpaceNOW`   | function  |
| `frameBuffer` | `DrawBoardPattern1Space`      | function  |
| `frameBuffer` | `DrawBoardPattern`            | function  |
| `frameBuffer` | `Draw`                        | function  |
|               | `Ghost`                       |   class   |

---

### UnitData.h

#### Takes

| From | Namespace | Identifier |
| ---- | :-------: | ---------- |

#### Gives

| Namespace | Identifier  |  Kind  |
| :-------: | ----------- | :----: |
|           | `Piece`     |  enum  |
|           | `UnitColor` |  enum  |
|           | `UnitData`  | struct |

---

### Board.h

#### Takes

| From       |   Namespace   | Identifier      |
| ---------- | :-----------: | --------------- |
| vector     |     `std`     | `vector`        |
| UnitData.h |               | `UnitData`      |
| UnitData.h |               | `UnitColor`     |
| Utils.h    | `space::game` | `sideTileCount` |
| Utils.h    |               | `Coord`         |
| Windows.h  |               | `COLORREF`      |

#### Gives

| Namespace | Identifier         |   Kind   |
| :-------: | ------------------ | :------: |
|           | `BoardStateMemory` |  class   |
|           | `MakeUnitData`     | function |
|           | `Phase`            |   enum   |
|           | `Board`            |  class   | // Might change this to a namespace

---

### Unit.h

#### Takes

| From       |   Namespace   | Identifier    |
| ---------- | :-----------: | ------------- |
| Utils.h    | `space::game` | sideTileCount |
| Utils.h    |               | Coord         |
| UnitData.h |               | UnitColor     |

#### Gives

| Namespace | Identifier   |  Kind  |
| :-------: | ------------ | :----: |
|           | `PieceMoves` | struct |

---

### Input.h

#### Takes

| From     | Namespace | Identifier           |
| -------- | :-------: | -------------------- |
| Window.h |           | `HANDLE`             |
| Window.h |           | `MOUSE_EVENT_RECORD` |
| Utils.h  |           | `Coord`              |

#### Gives

| Namespace | Identifier    |   Kind   |
| :-------: | ------------- | :------: |
|           | `g_console`   | variable |
|           | `outh`        | variable |
|           | `Mouse`       |  class   |
|           | `g_mouse`     | variable |
|           | `InitInput()` | function |
|           | `PingInput()` | function |

---

### UnitDirections.h

#### Takes

| From    | Namespace | Identifier |
| ------- | :-------: | ---------- |
| Utils.h |           | `Coord`    |

#### Gives

| Namespace | Identifier    |   Kind   |
| :-------: | ------------- | :------: |
|           | `Cardinal()`  | function |
|           | `Diagonal()`  | function |
|           | `Clockwise()` | function |
|           | `Knight()`    | function |

---

Order
===

0. concept
0. vector
0. Windows.h
0. Utils
0. Rendering
0. UnitData
0. Board
0. Unit
    - Pawn
    - Rook
    - Knight
    - Bishop
    - Queen
    - King
0. Input

Dependencies
===