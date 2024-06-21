#include<iostream>
#include<string>
#include<vector>

using namespace std;

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
        vector<string> buff;

    public:
        NcWindow(Point origin, Size size);

        void draw();
        void update_geometry(Point new_origin, Size new_size);

        void add_line(string line);
};
