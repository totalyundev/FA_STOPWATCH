#include <pebble.h>
#include "stopwatch.h"
#include "dialog_message_window.h"
static Window *s_main_window;
static TextLayer *s_textlayer_1;
static ActionBarLayer *s_action_bar_layer;
static GFont s_res_display_35;
static GBitmap *play_icon, *pause_icon, *tick_icon;
static int seconds=0;
static int minutes=0;


static bool play_action = false;


static int s_uptime = 1;
static void reset_variables(void) {
	seconds=0;
	minutes=0;
	play_action=false;
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  // Use a long-lived buffer
  static char s_uptime_buffer[32];

  // Get time since launch
  seconds = s_uptime % 60;
  minutes = (s_uptime % 3600) / 60;

  // Update the TextLayer
	if(seconds<10){
  snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "%d:0%d",  minutes, seconds);
  text_layer_set_text(s_textlayer_1, s_uptime_buffer);
}
	else {
		snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "%d:%d",  minutes, seconds);
  text_layer_set_text(s_textlayer_1, s_uptime_buffer);
		
	}
  // Increment s_uptime
  s_uptime++;
}

static void back_click_handler(ClickRecognizerRef recognizer, void *context) {
	//do nothing
	return;
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	//save
	if(play_action==false&&seconds>0){
		//save time and pop window & display save statement
		 dialog_message_window_push();
	}
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	//play/pause, tick_handler
	//start count uptime
	if (play_action == false) {
			action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_SELECT, pause_icon);	
			play_action =true;
				tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
					action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, NULL);	

	}
	//pause count uptime
	else {
			action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_SELECT, play_icon);	
			play_action =false;
				tick_timer_service_unsubscribe();
					action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, tick_icon);	

	}

}

static void click_config_provider(void *context) {
		window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
		window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
	window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);

}

static void window_load(Window *window) {
	 Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
	//load font
	 s_res_display_35 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DISPLAY_35));
	//txt layer for counter
	s_textlayer_1 = text_layer_create(GRect(-10, 62, 120, 54));
  text_layer_set_text(s_textlayer_1, "0:00");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_1, s_res_display_35);
  layer_add_child(window_get_root_layer(s_main_window), (Layer *)s_textlayer_1);
	//LOAD BITMAPS
	play_icon = gbitmap_create_with_resource(RESOURCE_ID_PLAY_ICON);
	pause_icon = gbitmap_create_with_resource(RESOURCE_ID_PAUSE_ICON);
	tick_icon = gbitmap_create_with_resource(RESOURCE_ID_TICK_ICON);
	//acton_bar
	s_action_bar_layer = action_bar_layer_create();
	action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_SELECT, play_icon);
	action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, tick_icon);
	action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, NULL);

	action_bar_layer_add_to_window(s_action_bar_layer, window);
	action_bar_layer_set_click_config_provider(s_action_bar_layer, click_config_provider);
	reset_variables();
}

static void window_unload(Window *window) {
 
  window_destroy(window);
  s_main_window = NULL;
}

void show_stopwatch() {
  if(!s_main_window) {
    s_main_window = window_create();
    window_set_background_color(s_main_window, GColorWhite);
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        //.unload = window_unload,
    });
  }
	 window_set_click_config_provider(s_main_window, (ClickConfigProvider)click_config_provider);
  window_stack_push(s_main_window, true);
}

void hide_stopwatch(void) {
	 window_destroy(s_main_window);
  s_main_window = NULL;
	window_stack_remove(s_main_window, true);
	
	
}