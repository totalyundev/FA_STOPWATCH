/*

#include <pebble.h>
#include "stopwatch.h"
#include "animated_ab.h"
static Window *s_window;

static GFont s_res_gothic_18_bold;
static GFont custom_font_42;
static GFont display_font_30;
static GFont s_res_display_30;

static TextLayer *s_counter_text_layer;
static TextLayer *s_textlayer_1;

static BitmapLayer *s_bitmaplayer_1;

static GBitmap *clock_bitmap, *play_bitmap, *pause_bitmap;

ActionBarLayer *action_bar;

static int s_uptime = 1;
static int s_counter =0;

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  // Use a long-lived buffer
  static char s_uptime_buffer[32];

  // Get time since launch
  int seconds = s_uptime % 60;
  int minutes = (s_uptime % 3600) / 60;

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

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	
//start/stop
bitmap_layer_destroy(s_bitmaplayer_1);	
	
	s_counter++;
	switch (s_counter){

	case 1:	
		tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
		action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, pause_bitmap);
	
		//text_layer_set_text(s_textlayer_1, "Stop");
return;
		case 2:
		tick_timer_service_unsubscribe();
		//show question window
		psleep(1200);
	hide_actionbar(action_bar);
		//	text_layer_set_text(s_textlayer_1, "quest_win");
//		show_question_screen();
		return;
	}

}


static void click_config_provider(void *context) {
		window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	
}

static void initialise_ui(void) {
  s_window = window_create();
 //display_font_30= fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DISPLAY_50));
 //custom_font_42 =fonts_load_custom_font(resource_get_handle(RESOURCE_ID_STOPWATCH_FONT_28));
 s_res_display_30 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DISPLAY_35));
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(-10, 62, 120, 54));
  text_layer_set_text(s_textlayer_1, "0:00");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_1, s_res_display_30);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
	*/
	/*
  // s_counter_text_layer
  s_counter_text_layer = text_layer_create(GRect(10, 100, 150, 100));
  text_layer_set_text(s_counter_text_layer, "0:00");
  text_layer_set_text_alignment(s_counter_text_layer, GTextAlignmentLeft);
text_layer_set_font(s_counter_text_layer, display_font_30);
	layer_add_child(window_get_root_layer(s_window), (Layer *)s_counter_text_layer);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(20, 55, 100, 40));
  text_layer_set_text(s_textlayer_1, "Start");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
	
	//
*/
/*	
	// s_bitmaplayer_1
	clock_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CLOCK_IMG);
  s_bitmaplayer_1 = bitmap_layer_create(GRect(7, 20, 128, 128));
  bitmap_layer_set_background_color(s_bitmaplayer_1, GColorClear);
	bitmap_layer_set_bitmap(s_bitmaplayer_1,clock_bitmap);
  //layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_1);
	
	//actionbar layer
 // Initialize the action bar:
  action_bar = action_bar_layer_create();
  // Associate the action bar with the window:
  action_bar_layer_add_to_window(action_bar, s_window);
  // Set the click config provider:
  action_bar_layer_set_click_config_provider(action_bar, click_config_provider);
	
	play_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PLAY_ICON);
	pause_bitmap = gbitmap_create_with_resource(RESOURCE_ID_PAUSE_ICON);
	
	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, play_bitmap);
  show_actionbar(action_bar);

	
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_counter_text_layer);
  text_layer_destroy(s_textlayer_1);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}



void show_stopwatch(void) {
	 initialise_ui();
		 window_set_click_config_provider(s_window, (ClickConfigProvider)click_config_provider);

  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
	
}
void hide_stopwatch(void) {
	window_stack_remove(s_window, true);
	
	
}
*/