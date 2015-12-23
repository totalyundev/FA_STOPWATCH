#include <pebble.h>
#include "first_menu.h"



static void handle_init(void) {
	show_first_menu();
	
	
}

static void handle_deinit(void) {
	
	
	
}


int main() {
	handle_init();
	app_event_loop();
	handle_deinit();
	return 0;
}