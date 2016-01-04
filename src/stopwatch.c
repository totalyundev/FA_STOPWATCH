#include <pebble.h>
#include "stopwatch.h"
#include "dialog_message_window.h"
static Window *s_main_window;
static TextLayer *s_textlayer_1, *s_title_textlayer, *s_down_textlayer;
static ActionBarLayer *s_action_bar_layer;
static GFont s_res_display_35;
static GBitmap *play_icon, *pause_icon, *tick_icon;
static int seconds=0;
static int minutes=0;


static bool play_action = false;
static char event_title[4][32];

static int s_uptime = 1;
static void reset_variables(void) {
	seconds=0;
	minutes=0;
	play_action=false;
}

static void stopwatch_display(int seconds, int minutes) {
	//right way to display all of zeros  
	 // Use a long-lived buffer
	static char s_uptime_buffer[32];

	if(seconds<10 && minutes<10){
  snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "0%d:0%d",  minutes, seconds);
  text_layer_set_text(s_textlayer_1, s_uptime_buffer);
	}
	else if(minutes<10 && seconds>10) {
		snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "0%d:%d",  minutes, seconds);
  text_layer_set_text(s_textlayer_1, s_uptime_buffer);
	}
  else if(seconds>10 && minutes>10) {
		snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "%d:%d",  minutes, seconds);
  text_layer_set_text(s_textlayer_1, s_uptime_buffer);
	}
  else if(seconds<10 && minutes>10) {
		snprintf(s_uptime_buffer, sizeof(s_uptime_buffer), "%d:0%d",  minutes, seconds);
  text_layer_set_text(s_textlayer_1, s_uptime_buffer);
	}
  
	
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  // Get time since launch
  seconds = s_uptime % 60;
  minutes = (s_uptime % 3600) / 60;
stopwatch_display(seconds,minutes);
  // Update the TextLayer
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
		action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, NULL);	
		action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_SELECT, pause_icon);	
			play_action =true;
			tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
			text_layer_set_text(s_down_textlayer, " ");
	layer_set_hidden((Layer *)s_title_textlayer, true);
		//text_layer_set_text(s_title_textlayer, "");
	}
	//pause count uptime
	else {
		action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_DOWN, tick_icon);	
		action_bar_layer_set_icon(s_action_bar_layer, BUTTON_ID_SELECT, play_icon);	
			play_action =false;
			tick_timer_service_unsubscribe();
			text_layer_set_text(s_down_textlayer, "Zakończ");
		layer_set_hidden((Layer *)s_title_textlayer, false);
	}

}

static void click_config_provider(void *context) {
		window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
		window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
	window_single_click_subscribe(BUTTON_ID_BACK, back_click_handler);

}
static void load_title(int index) {
	snprintf(event_title[0],sizeof(event_title[0]), "Event type 1");
	snprintf(event_title[1],sizeof(event_title[1]), "Event type 2");
	snprintf(event_title[2],sizeof(event_title[2]), "Event type 3");
	snprintf(event_title[3],sizeof(event_title[3]), "Event type 4");	
    APP_LOG(APP_LOG_LEVEL_INFO, "load title:%d",index);
	text_layer_set_text(s_title_textlayer, event_title[index]);
  APP_LOG(APP_LOG_LEVEL_INFO, "title loaded");
	
}
static void window_load(Window *window) {
	 Layer *window_layer = window_get_root_layer(window);
 // GRect bounds = layer_get_bounds(window_layer);
	//load font
	 s_res_display_35 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DISPLAY_35));
	//txt layer for zakoncz
	s_down_textlayer =text_layer_create(GRect(5, 120, 100, 50));
	text_layer_set_text(s_down_textlayer, "");
	text_layer_set_text_alignment(s_down_textlayer, GTextAlignmentRight);
	text_layer_set_font(s_down_textlayer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	layer_add_child(window_layer, (Layer *)s_down_textlayer);
	//txt layer for counter
	s_textlayer_1 = text_layer_create(GRect(-10, 62, 120, 54));
  text_layer_set_text(s_textlayer_1, "00:00");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_1, s_res_display_35);
  layer_add_child(window_layer, (Layer *)s_textlayer_1);
	//txt layer for event type
	s_title_textlayer = text_layer_create(GRect(5,5,120,40));
  text_layer_set_text(s_title_textlayer, "");
	text_layer_set_text_alignment(s_title_textlayer, GTextAlignmentLeft);
	text_layer_set_font(s_title_textlayer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	layer_add_child(window_layer, (Layer *)s_title_textlayer);
	

	
	
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
	//load_title();
}

static void window_unload(Window *window) {
 
  window_destroy(window);
  s_main_window = NULL;
}

void show_stopwatch(int index) {
  if(!s_main_window) {
	//	event_title = *event_title_buffer;
   			  APP_LOG(APP_LOG_LEVEL_INFO, "Stopwatch index:%d",index);
	
		s_main_window = window_create();
    window_set_background_color(s_main_window, GColorWhite);
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
       .unload = window_unload,
    });
  }
	 window_set_click_config_provider(s_main_window, (ClickConfigProvider)click_config_provider);
  window_stack_push(s_main_window, true);
		load_title(index);
	
}

void hide_stopwatch(void) {
	// window_destroy(s_main_window);
 // s_main_window = NULL;
	window_stack_remove(s_main_window, true);
	
	
}