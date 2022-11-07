#include "main.h"
#include "selector/button.hpp"

Button::Button(int x, int y, int w, int h, int type) {
    b_x = x;
    b_y = y;
    b_w = w;
    b_h = h;
    b_type = type;
}

void Button::draw() {
    switch (b_type) {
        case 0:
            pros::screen::set_pen(COLOR_RED);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, b_x + b_w / 2, b_y + b_h / 2, "RED\nROLLER START");
            break;
        case 1:
            pros::screen::set_pen(COLOR_RED);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, b_x + b_w / 2, b_y + b_h / 2, "RED\nNO ROLLER START");
            break;
        case 2:
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, b_x + b_w / 2, b_y + b_h / 2, "BLUE\nROLLER START");
            break;
        case 3:
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, b_x + b_w / 2, b_y + b_h / 2, "BLUE\nNO ROLLER START");
            break;
        case 4:
            pros::screen::set_pen(COLOR_YELLOW);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::set_pen(COLOR_WHITE);
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, b_x + b_w / 2, b_y + b_h / 2, "SKILLS");
            break;
    }
}

void Button::test_click() {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();
    if (status.x > b_x && status.x < b_x + b_w && status.y > b_y && status.y < b_y + b_h) {
        program = b_type;
        selected = true;
    }
}