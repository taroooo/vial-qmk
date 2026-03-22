/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include QMK_KEYBOARD_H

enum custom_keycodes {
    DS_TOG = QK_KB_0,
    DS_MOM = QK_KB_1,
    PRECISION = QK_KB_2,
};

static bool ds_mom_active = false;
static bool precision_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DS_TOG:
            if (record->event.pressed) {
                ds_mom_active = !ds_mom_active;
            }
            return false;
        case DS_MOM:
            ds_mom_active = record->event.pressed;
            return false;
        case PRECISION:
            precision_active = record->event.pressed;
            return false;
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (ds_mom_active) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    if (precision_active) {
        mouse_report.x = mouse_report.x / 4;
        mouse_report.y = mouse_report.y / 4;
    }
    return mouse_report;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( KC_BTN4, KC_BTN5, DS_MOM, KC_BTN2, KC_BTN1, KC_BTN3 )
};
