#include "main.h"
#include "selector/display.hpp"

void display() {
    pros::screen::set_pen(COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);
    Button buttons[5] = {Button(130, 64, 80, 34, 0), 
                         Button(270, 64, 80, 34, 1),
                         Button(130, 118, 80, 34, 2),
                         Button(270, 118, 80, 34, 3),
                         Button(200, 171, 80, 34, 4)};

    for (int i = 0; i < 5; i++) {
        buttons[i].draw();
    }
}

void display_selected() {
    pros::screen::set_pen(COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);
    pros::screen::set_pen(COLOR_WHITE);
    switch (program) {
        case 0:
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 240, 120, "Program selected: RED/ROLLER START");
            break;
        case 1:
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 240, 120, "Program selected: RED/NO ROLLER START");
            break;
        case 2: 
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 240, 120, "Program selected: BLUE/ROLLER START");
            break;
        case 3:
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 240, 120, "Program selected: BLUE/NO ROLLER START");
            break;
        case 4:
            pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 240, 120, "Program selected: SKILLS");
            break;
    }
}

void on_click() {
    Button buttons[5] = {Button(130, 64, 80, 34, 0), 
                         Button(270, 64, 80, 34, 1),
                         Button(130, 118, 80, 34, 2),
                         Button(270, 118, 80, 34, 3),
                         Button(200, 171, 80, 34, 4)};

    for (int i = 0; i < 5; i++) {
        buttons[i].test_click();
    }
}

void empty() {}

void run_selector() {
    selected = false;
    while (true) {
        if (!selected) {
            pros::screen::touch_callback(on_click, pros::E_TOUCH_RELEASED);
            display();
            
        } else {
            pros::screen::touch_callback(empty, pros::E_TOUCH_RELEASED);
            display_selected();
        }
        pros::delay(20);
    }
}