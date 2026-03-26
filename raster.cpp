#include "raster.h"
#include <algorithm>
#include <iostream>

using namespace std;

Frame buildEmptyFrame(size_t width, size_t height) {
    Frame frame;
    string emptyLine(width, ' ');
    for (size_t i = 0; i < height; i++) {
        frame.push_back(emptyLine);
    }
    return frame;
}

Frame buildEmptySquareFrame(size_t size) {
    return buildEmptyFrame(2* size, size);
}

void showFrame(const Frame& frame) {
    for (size_t i = 0; i < frame.size(); i++) {
        cout << frame[i] << endl;
    }
}

void clearScreen() {
    cout << "\033[2J\033[H";
}

bool pointInFrame(const Frame& frame, const GridPoint& p) {
    return pointInFrame(frame, p.x, p.y);
}

bool pointInFrame(const Frame& frame, int x, int y) {
    size_t height = frame.size();
    size_t width = frame[0].size();

    if (!(0 <= x && x < (int)width)) {
        return false;
    }
    if (!(0 <= y && y < (int)height)) {
        return false;
    }
    return true;
}

bool pointInTriangle(const GridPoint& p, const GridTriangle& t) {
    auto edge = [](GridPoint a, GridPoint b, GridPoint p) {
        return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    };

    int e1 = edge(t.p1, t.p2, p);
    int e2 = edge(t.p2, t.p3, p);
    int e3 = edge(t.p3, t.p1, p);

    return (e1 >= 0 && e2 >= 0 && e3 >= 0) ||
           (e1 <= 0 && e2 <= 0 && e3 <= 0);
}

void drawPoint(Frame& frame, const GridPoint p, char c) {
    frame[p.y][p.x] = c;
}

void drawLine(Frame& frame, GridPoint p1, GridPoint p2, char c){
    if (p1.x == p2.x && p1.y == p2.y) {
        if (pointInFrame(frame, p1)) {
            frame[p1.y][p1.x] = c;      
        }
        return;
    }

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    if (abs(dy) < abs(dx)) {
        // Loop over x
        float gradient = float(dy) / dx;
        if (p1.x > p2.x) {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }
        for (int x = p1.x; x <= p2.x; x++) {
            int y = int(round(p1.y + (x - p1.x) * gradient));
            if (pointInFrame(frame, x, y)) {
                frame[y][x] = c;
            }
        }

    } else {
        // Loop over y
        float invGradient = float(dx) / dy;
        if (p1.y > p2.y) {
            swap(p1.x, p2.x);
            swap(p1.y, p2.y);
        }

        for (int y = p1.y; y <= p2.y; y++) {
            int x = int(round(p1.x + (y - p1.y) * invGradient));
            if (pointInFrame(frame, x, y)) {
                frame[y][x] = c;
            }
        }
    }
}

BoundingBox triangleBBox(const Frame& frame, const GridTriangle& t) {
    size_t height = frame.size();
    size_t width = frame[0].size();
    int minx = min(t.p1.x, min(t.p2.x, t.p3.x));
    int maxx = max(t.p1.x, max(t.p2.x, t.p3.x));
    int miny = min(t.p1.y, min(t.p2.y, t.p3.y));
    int maxy = max(t.p1.y, max(t.p2.y, t.p3.y));
    minx = max(0, minx);
    maxx = min(maxx, (int)width - 1);
    miny = max(0, miny);
    maxy = min(maxy, (int)height - 1);

    BoundingBox result = {minx, maxx, miny, maxy};
    return result;
}

void drawTriangleOutline(Frame& frame, const GridTriangle& t, char c) {
    drawLine(frame, t.p1, t.p2, c);
    drawLine(frame, t.p2, t.p3, c);
    drawLine(frame, t.p3, t.p1, c);
}

void drawTriangle(Frame& frame, const GridTriangle& t, char c) {
    BoundingBox bbox = triangleBBox(frame, t);
    for (int y = bbox.miny; y <= bbox.maxy; y++){
        for (int x = bbox.minx; x <= bbox.maxx; x++) {
            GridPoint p = {x, y};
            if (pointInTriangle(p, t)) {
                frame[y][x] = c;
            }
        }
    }
    drawTriangleOutline(frame, t, c);
}