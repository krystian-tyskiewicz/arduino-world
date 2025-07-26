#ifndef COMMON_H
#define COMMON_H

#define BLACK   0x0000
#define WHITE   0xFFFF
#define BLUE    0x001F
#define GREEN   0x07E0
#define ORANGE  0xFD20
#define RED     0xF800
#define YELLOW  0xFFE0

struct ScreenPoint {
    int x;
    int y;
};

class View {
public:
    virtual void draw();
    virtual void handleScreenPoint(ScreenPoint screenPoint);
};

#endif
