#pragma once

class Button {
    private:
        int b_x;
        int b_y;
        int b_w;
        int b_h;
        int b_type;
    public: 
        Button(int x, int y, int w, int h, int type);

        void draw();
        void test_click();
        void display_selected();
};