#include "main.h"
#include "selector/button.hpp"

Button::Button(int x, int y, int w, int h, int type) {
    b_x = x;
    b_y = y;
    b_w = w;
    b_h = h;
    b_type = type;
}

void Button::draw(void) {
    switch (b_type) {
        case 0:
            pros::screen::set_pen(COLOR_RED);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::print(pros::E_TEXT_SMALL, b_x + b_w / 2 - 58, b_y + b_h / 2 - 5, "RED ROLLER START");
            break;
        case 1:
            pros::screen::set_pen(COLOR_RED);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::print(pros::E_TEXT_SMALL, b_x + b_w / 2 - 71, b_y + b_h / 2 - 5, "RED NO ROLLER START");
            break;
        case 2:
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::print(pros::E_TEXT_SMALL, b_x + b_w / 2 - 65, b_y + b_h / 2 - 5, "BLUE ROLLER START");
            break;
        case 3:
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::print(pros::E_TEXT_SMALL, b_x + b_w / 2 - 76, b_y + b_h / 2 - 5, "BLUE NO ROLLER START");
            break;
        case 4:
            pros::screen::set_pen(COLOR_YELLOW);
            pros::screen::draw_rect(b_x, b_y, b_x + b_w, b_y + b_h);
            pros::screen::print(pros::E_TEXT_SMALL, b_x + b_w / 2 - 23, b_y + b_h / 2 - 5, "SKILLS");
            break;
    }
}

void Button::display_selected(void) {
    pros::screen::set_pen(COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);
    pros::screen::set_pen(COLOR_WHITE);
    switch (b_type) {
        case 0:
            pros::screen::print(pros::E_TEXT_SMALL, 240, 120, "Program selected: RED/ROLLER START");
            break;
        case 1:
            pros::screen::print(pros::E_TEXT_SMALL, 240, 120, "Program selected: RED/NO ROLLER START");
            break;
        case 2: 
            pros::screen::print(pros::E_TEXT_SMALL, 240, 120, "Program selected: BLUE/ROLLER START");
            break;
        case 3:
            pros::screen::print(pros::E_TEXT_SMALL, 240, 120, "Program selected: BLUE/NO ROLLER START");
            break;
        case 4:
            pros::screen::print(pros::E_TEXT_SMALL, 240, 120, "Program selected: SKILLS");
            break;
    }
}

void Button::test_click(void) {
    pros::screen_touch_status_s_t status = pros::screen::touch_status();
    if (status.x > b_x && status.x < b_x + b_w && status.y > b_y && status.y < b_y + b_h) {
        program = b_type;
        selected = true;
        display_selected();
    }
}