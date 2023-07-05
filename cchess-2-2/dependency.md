# Order of dependencies

Headers will not be included until they are absolutely needed, with the exception of external libraries.

If a header only references identifiers without using them, they will be forward declared instead of including the related header.

Order
===

0. External libs
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

### Utils

#### Takes

| From      | Namespace | Identifier            |   Kind   |
| --------- | :-------: | --------------------- | :------: |
| Windows.h |           | `HWND`                | typedef  |
| Windows.h |           | `HDC`                 | typedef  |
| concepts  |   `std`   | `is_integral_v`       | template |
| concepts  |   `std`   | `is_floating_point_v` | template |
| concepts  |   `std`   | `integral`            | concept  |
| concepts  |   `std`   | `floating_point`      | concept  |

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
|           | `BiardTile`    |  struct   |

---

### Rendering

#### Takes

| From      | Namespace | Identifier |  Kind   |
| --------- | :-------: | ---------- | :-----: |
| Windows.h |           | `COLORREF` | typedef |
| Windows.h |           | `UINT`     | typedef |

#### Gives

|  Namespace  | Identifier                    |   Kind    |
| :---------: | ----------------------------- | :-------: |
|             | `Color`                       |  struct   |
|             | `CRef()`                      | function  |
|             | `sprite`                      | namespace |
|   sprite    | `Pltt`                        |   enum    |
|   sprite    | `colorPalette[]`              |   array   |
|   sprite    | `PaletteColor()`              | function  |
|   sprite    | `Sprite`                      |  struct   |
|   sprite    | `unit`                        | namespace |
|   sprite    | `symbol`                      | namespace |
|             | `frameBuffer`                 | namespace |
| frameBuffer | `Index`                       | function  |
| frameBuffer | `IsValidPxPosition`           | function  |
| frameBuffer | `Get`                         | function  |
| frameBuffer | `SpacePatternAtPos`           | function  |
| frameBuffer | `DrawPixel`                   | function  |
| frameBuffer | `DrawPixelSafe`               | function  |
| frameBuffer | `DrawToBufferAndScreen`       | function  |
| frameBuffer | `WriteToBuffer`               | function  |
| frameBuffer | `DrawToBufferSafe`            | function  |
| frameBuffer | `DrawSpriteNOW`               | function  |
| frameBuffer | `DrawSymbolSkippingBuffer`    | function  |
| frameBuffer | `DrawSpriteWithBackgroundNOW` | function  |
| frameBuffer | `BufferCleanplateSpace`       | function  |
| frameBuffer | `DrawGhost`                   | function  |
| frameBuffer | `DrawSprite`                  | function  |
| frameBuffer | `DrawRectNOW`                 | function  |
| frameBuffer | `DrawRect`                    | function  |
| frameBuffer | `DrawGridSpaceNOW`            | function  |
| frameBuffer | `DrawGridSpace`               | function  |
| frameBuffer | `DrawBoardPattern1SpaceNOW`   | function  |
| frameBuffer | `DrawBoardPattern1Space`      | function  |
| frameBuffer | `DrawBoardPattern`            | function  |
| frameBuffer | `Draw`                        | function  |
|             | `Ghost`                       |   class   |

---

### UnitData

#### Takes

| From | Namespace | Identifier | Kind |
| ---- | :-------: | ---------- | :--: |

#### Gives

| Namespace | Identifier  |  Kind  |
| :-------: | ----------- | :----: |
|           | `Piece`     |  enum  |
|           | `UnitColor` |  enum  |
|           | `UnitData`  | struct |

---

### Board

#### Takes

| From | Namespace | Identifier | Kind |
| ---- | :-------: | ---------- | :--: |

#### Gives

| Namespace | Identifier  |  Kind  |
| :-------: | ----------- | :----: |

---

### Unit

#### Takes

-

#### Gives

-

---

### Input

#### Takes

-

#### Gives

-

---

### UnitDirections

#### Takes

-

#### Gives

-

---

### Main

#### Takes

-

#### Gives

-

---
