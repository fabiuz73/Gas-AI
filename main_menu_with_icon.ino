#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "monitor_logo.c"  // Logo per "Monitoraggio"
#include "settings_logo.c" // Logo per "Impostazioni"

// Touchscreen pins
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

// Reference to screens
lv_obj_t *menu_screen;
lv_obj_t *settings_screen;
lv_obj_t *monitor_screen;

// Callback to switch screens
void switch_screen(lv_obj_t *new_screen) {
  lv_scr_load_anim(new_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 300, 0, false);
}

// Main menu screen creation
void create_menu_screen() {
  menu_screen = lv_obj_create(NULL);

  // Title
  lv_obj_t *title = lv_label_create(menu_screen);
  lv_label_set_text(title, "Menu Principale");
  lv_obj_set_style_text_color(title, lv_color_hex(0x333333), LV_PART_MAIN);
  lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

  // Button for "Monitoraggio"
  lv_obj_t *monitor_btn = lv_btn_create(menu_screen);
  lv_obj_set_size(monitor_btn, 100, 100); // Cambia dimensione
  lv_obj_align(monitor_btn, LV_ALIGN_CENTER, -60, 10);
  lv_obj_add_event_cb(monitor_btn, [](lv_event_t *e) {
    switch_screen(monitor_screen);
  }, LV_EVENT_CLICKED, NULL);

  // Add logo to "Monitoraggio"
  lv_obj_t *monitor_img = lv_img_create(monitor_btn);
  lv_img_set_src(monitor_img, &monitor_logo); // Usa il logo convertito
  lv_obj_center(monitor_img);

  // Button for "Impostazioni"
  lv_obj_t *settings_btn = lv_btn_create(menu_screen);
  lv_obj_set_size(settings_btn, 100, 100); // Cambia dimensione
  lv_obj_align(settings_btn, LV_ALIGN_CENTER, 60, 10);
  lv_obj_add_event_cb(settings_btn, [](lv_event_t *e) {
    switch_screen(settings_screen);
  }, LV_EVENT_CLICKED, NULL);

  // Add logo to "Impostazioni"
  lv_obj_t *settings_img = lv_img_create(settings_btn);
  lv_img_set_src(settings_img, &settings_logo); // Usa il logo convertito
  lv_obj_center(settings_img);
}

// Monitor screen creation
void create_monitor_screen() {
  monitor_screen = lv_obj_create(NULL);

  // Title
  lv_obj_t *title = lv_label_create(monitor_screen);
  lv_label_set_text(title, "Monitoraggio");
  lv_obj_set_style_text_color(title, lv_color_hex(0x333333), LV_PART_MAIN);
  lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

  // Back button
  lv_obj_t *back_btn = lv_btn_create(monitor_screen);
  lv_obj_set_size(back_btn, 100, 50);
  lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
  lv_obj_t *back_label = lv_label_create(back_btn);
  lv_label_set_text(back_label, "Indietro");
  lv_obj_center(back_label);
  lv_obj_add_event_cb(back_btn, [](lv_event_t *e) {
    switch_screen(menu_screen);
  }, LV_EVENT_CLICKED, NULL);
}

// Settings screen creation
void create_settings_screen() {
  settings_screen = lv_obj_create(NULL);

  // Title
  lv_obj_t *title = lv_label_create(settings_screen);
  lv_label_set_text(title, "Impostazioni");
  lv_obj_set_style_text_color(title, lv_color_hex(0x333333), LV_PART_MAIN);
  lv_obj_set_style_text_font(title, &lv_font_montserrat_20, LV_PART_MAIN);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);

  // Back button
  lv_obj_t *back_btn = lv_btn_create(settings_screen);
  lv_obj_set_size(back_btn, 100, 50);
  lv_obj_align(back_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
  lv_obj_t *back_label = lv_label_create(back_btn);
  lv_label_set_text(back_label, "Indietro");
  lv_obj_center(back_label);
  lv_obj_add_event_cb(back_btn, [](lv_event_t *e) {
    switch_screen(menu_screen);
  }, LV_EVENT_CLICKED, NULL);
}

// Touchscreen data retrieval
void touchscreen_read(lv_indev_t *indev, lv_indev_data_t *data) {
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = x;
    data->point.y = y;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize LVGL
  lv_init();

  // Initialize touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(2);

  // Initialize TFT display
  lv_display_t *disp;
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);

  // Initialize touchscreen input device
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchscreen_read);

  // Create screens
  create_menu_screen();
  create_monitor_screen();
  create_settings_screen();

  // Load menu screen as the default
  lv_scr_load(menu_screen);
}

void loop() {
  lv_task_handler();
  lv_tick_inc(5);
  delay(5);
}