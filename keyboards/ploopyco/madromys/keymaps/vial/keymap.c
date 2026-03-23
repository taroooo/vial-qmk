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
        static int16_t acc_x = 0;
        static int16_t acc_y = 0;
        acc_x += mouse_report.x;
        acc_y += mouse_report.y;
        mouse_report.x = acc_x / 4;
        mouse_report.y = acc_y / 4;
        acc_x -= mouse_report.x * 4;
        acc_y -= mouse_report.y * 4;
    }
    if (ds_active) {
        static int16_t acc_h = 0;
        static int16_t acc_v = 0;
        acc_h += mouse_report.x;
        acc_v += mouse_report.y;
        mouse_report.h = acc_h / 8;
        mouse_report.v = -(acc_v / 8);
        acc_h -= mouse_report.h * 8;
        acc_v -= (acc_v / 8) * 8;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( KC_BTN4, KC_BTN5, DS_MOM, KC_BTN2, KC_BTN1, KC_BTN3 )
};
