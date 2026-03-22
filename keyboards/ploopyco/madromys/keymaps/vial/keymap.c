#include QMK_KEYBOARD_H

enum custom_keycodes {
    DS_TOG = QK_KB_2,
    DS_MOM = QK_KB_3,
    PRECISION = QK_KB_4,
};

static bool ds_active = false;
static bool precision_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DS_TOG:
            if (record->event.pressed) {
                ds_active = !ds_active;
            }
            return false;
        case DS_MOM:
            ds_active = record->event.pressed;
            return false;
        case PRECISION:
            precision_active = record->event.pressed;
            return false;
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (precision_active) {
        mouse_report.x = mouse_report.x / 4;
        mouse_report.y = mouse_report.y / 4;
    }
    if (ds_active) {
        mouse_report.h = mouse_report.x / 8;
        mouse_report.v = -mouse_report.y / 8;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( KC_BTN4, KC_BTN5, DS_MOM, KC_BTN2, KC_BTN1, KC_BTN3 )
};
