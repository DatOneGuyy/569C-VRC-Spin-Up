#include "main.h"
#include "selector/display.hpp"

void display() {
    pros::screen::set_pen(COLOR_BLACK);
    pros::screen::fill_rect(0, 0, 480, 240);
    Button buttons[5] = {Button(30, 20, 195, 160 / 3, 0), 
                         Button(255, 20, 195, 160/3, 1),
                         Button(30, 40 + 160 / 3, 195, 160 / 3, 2),
                         Button(255, 40 + 160 / 3, 195, 160 / 3, 3),
                         Button(240 - 195 / 2, 60 + 320 / 3, 195, 160 / 3, 4)};

    for (int i = 0; i < 5; i++) {
        buttons[i].draw();
    }
}

void on_click() {
    Button buttons[5] = {Button(130, 64, 80, 34, 0), 
                         Button(270, 64, 80, 34, 1),
                         Button(130, 118, 80, 34, 2),
                         Button(270, 118, 80, 34, 3),
                         Button(200, 171, 80, 34, 4)};
    if (!selected) {
        for (int i = 0; i < 5; i++) {
            buttons[i].test_click();
        }
    } else {

    }
}

void empty() {
    pros::screen::set_pen(COLOR_WHITE);
    pros::screen::fill_circle(50, 50, 100);
    printf("touch");
}

void run_selector() {
    pros::screen::print(pros::E_TEXT_SMALL, 1 ,"start");
    selected = false;
    pros::screen::touch_callback(empty, TOUCH_RELEASED);
    display();
    while (true) {
		pros::delay(50);
	}
}