#include<iostream>
#include<string>

using namespace std;

// TODO: Some kind of namespase for Origin and Size

namespace Geometry {
    struct Point {
        int y;
        int x;
    };

    struct Size {
        int height;
        int width;
    };
}

using namespace Geometry;

class NcWindow {
    private:
        Point origin;
        Size size;

    public:
        NcWindow(Point origin, Size size);

        void draw();
        void add_line(string line);
};
