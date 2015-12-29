#include <pebble.h>
#include "first_menu.h"
#include "stopwatch.h"
#include "skaryfikacja.h"
#include "dialog_message_window.h"
#define NUM_MENU_ICONS 4
#define NUM_MENU_SECTIONS 1
#define NUM_FIRST_MENU_ITEMS 4
#define NUM_SECOND_MENU_ITEMS 4
#define NUM_THIRD_MENU_ITEMS 4
static Window *window;
static MenuLayer *menu_layer;
// if you want to use icons this is the way
//static GBitmap *menu_icons[NUM_MENU_ICONS];
static void display_stopwatch(void) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "clicked menu element");
    //and this is a temporary function, just calls a stopwatch
    show_stopwatch();
}


static int16_t get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context) {
  return PBL_IF_ROUND_ELSE(
    menu_layer_is_index_selected(menu_layer, cell_index) ?
      MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT : MENU_CELL_ROUND_UNFOCUSED_TALL_CELL_HEIGHT,
    LIST_MESSAGE_WINDOW_CELL_HEIGHT);
}

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
    return NUM_MENU_SECTIONS;
}
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    switch (section_index) {
        case 0:
        return NUM_FIRST_MENU_ITEMS;
        default:
        return 0;
    }
}
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    // This is a define provided in pebble.h that you may use for the default height
    // Header is disabled by setting 0. It must be declared.
    //return MENU_CELL_BASIC_HEADER_HEIGHT;
    return 0;
}
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    // Determine which section we're working with
    switch (section_index) {
        case 0:
        // Draw title text in the section header
        menu_cell_basic_header_draw(ctx, cell_layer, NULL);
        break;
    }
}
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
    // Determine which section we're going to draw in
    switch (cell_index->section) {
        case 0:
        // Use the row to specify which item we'll draw
        switch (cell_index->row) {
            case 0:
            menu_cell_basic_draw(ctx, cell_layer, "Timer", NULL,NULL);
            break;
            case 1:
            menu_cell_basic_draw(ctx, cell_layer, "Simple Event", NULL, NULL);
            break;
            case 2:
            menu_cell_basic_draw(ctx, cell_layer, "Pointless Button", NULL, NULL);
            break;
            case 3:
            menu_cell_basic_draw(ctx, cell_layer, "Quit", NULL, NULL);
            break;
        }
        break;
    }
}
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    // Use the row to specify which item will receive the select action
    //this is a place for callbacks for each element
    switch (cell_index->section) {
          case 0:
        // Use the row to specify which item we'll draw
        switch (cell_index->row) {
            case 0:
						display_stopwatch();
						break;
            case 1:
         	  dialog_message_window_push();  
            break;
            case 2:
            //   
            break;
            case 3:
            //  
						window_stack_pop_all(true);
            break;

				 		default:
				    display_stopwatch();
    				break;
				}
   
}
}
void window_load(Window *window) {
    // Here we load the bitmap assets
    // resource_init_current_app must be called before all asset loading
    /* how to st up icons
    int num_menu_icons = 0;
    menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_BIG_WATCH);
    menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_SECTOR_WATCH);
    menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_BINARY_WATCH);
    // And also load the background
    menu_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_BRAINS);
    */
    // Now we prepare to initialize the menu layer
    // We need the bounds to specify the menu layer's viewport size
    // In this case, it'll be the same as the window's
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_frame(window_layer);// Create the menu layer
    menu_layer = menu_layer_create(bounds);
    // Set all the callbacks for the menu layer
    menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_header_height = menu_get_header_height_callback,
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .select_click = menu_select_callback,
			.get_cell_height = get_cell_height_callback,
    });
    // Bind the menu layer's click config provider to the window for interactivity
    menu_layer_set_click_config_onto_window(menu_layer, window);
    // Add it to the window for display
    layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}
void window_unload(Window *window) {
    // Destroy the menu layer
    menu_layer_destroy(menu_layer);
    // Cleanup the menu icons
    //for (int i = 0; i < NUM_MENU_ICONS; i++) {
        //gbitmap_destroy(menu_icons[i]);
    }
    void show_first_menu(void) {
        window = window_create();
        // Setup the window handlers
        window_set_window_handlers(window, (WindowHandlers) {
            .load = window_load,
            .unload = window_unload,
        });
        window_stack_push(window, true);
    }
    void hide_first_menu(void) {
        window_destroy(window);
    }