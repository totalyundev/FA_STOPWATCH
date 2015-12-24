#include <pebble.h>
#include "skaryfikacja.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static BitmapLayer *s_bitmaplayer_1;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  // s_bitmaplayer_1
  s_bitmaplayer_1 = bitmap_layer_create(GRect(7, 20, 128, 128));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorWhite);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_1);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_skaryfikacja(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_skaryfikacja(void) {
  window_stack_remove(s_window, true);
}
