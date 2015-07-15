#include <pebble.h>
#include "TrainLayer.h"
  
#define KEY_STATION 0
#define KEY_DEPARTURETIME 1
#define KEY_FILTER_STATION 2
#define KEY_TRAINS 3
#define KEY_TRAIN_DESTINATION_STATION 4
#define KEY_TRAIN_VIA 5
#define KEY_SCHEDULED_DEPARTURE 6
#define KEY_EXPECTED_DEPARTURE 7
#define KEY_PLATFORM 8


static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_train1_layer;
static TextLayer *s_departure_station_layer;
static TextLayer *s_filter_station_layer;
static TextLayer *s_divider_line_1_layer;


// Store incoming information
static char station_buffer[32];
static char station_filter_buffer[32];
static char station_filter_buffer_formatted[32];
static char departureTime_buffer[32];
static char train_destinationstation_buffer[32];
static char train_via_buffer[32];
static char train_scheduled_departure_buffer[32];
static char train_expected_departure_buffer[32];
static char train_platform_buffer[32];

//static DictionaryIterator trains_iter;
//144 × 168 pixels

/*
struct TrainLayers
{
    int yPosition;
    TextLayer *s_train_line_1_layer;
    TextLayer *s_train_line_2_layer;
    TextLayer *s_train_line_3_layer;
    TextLayer *s_train_line_4_layer;
    char train_line_1_buffer_formatted[64];
    char train_line_2_buffer_formatted[64];
    char train_line_3_buffer_formatted[32];
    char train_line_4_buffer_formatted[32];
  
};
*/

static struct TrainLayers trainLayer1;  

/*void setupTrainLayer( struct TrainLayers *trainLayer, Window *window );

void setupTrainLayer( struct TrainLayers *trainLayer, Window *window )
{
  
  
   // Create Train Line 1 Layer
  trainLayer->s_train_line_1_layer = text_layer_create(GRect(0, trainLayer->yPosition, 144, 15));
  text_layer_set_background_color(trainLayer->s_train_line_1_layer, GColorClear);
  text_layer_set_text_color(trainLayer->s_train_line_1_layer, GColorBlack);
  text_layer_set_text_alignment(trainLayer->s_train_line_1_layer, GTextAlignmentLeft);
  text_layer_set_text(trainLayer->s_train_line_1_layer, "Test");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(trainLayer->s_train_line_1_layer));
  
    // Create Train Line 2 Layer
  trainLayer->s_train_line_2_layer = text_layer_create(GRect(14, trainLayer->yPosition + 15, 130, 15));
  text_layer_set_background_color(trainLayer->s_train_line_2_layer, GColorClear);
  text_layer_set_text_color(trainLayer->s_train_line_2_layer, GColorBlack);
  text_layer_set_text_alignment(trainLayer->s_train_line_2_layer, GTextAlignmentLeft);
  text_layer_set_text(trainLayer->s_train_line_2_layer, "");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(trainLayer->s_train_line_2_layer));
  
    // Create Train Line 3 Layer
  trainLayer->s_train_line_3_layer = text_layer_create(GRect(14, trainLayer->yPosition + 30, 58, 15));
  text_layer_set_background_color(trainLayer->s_train_line_3_layer, GColorClear);
  text_layer_set_text_color(trainLayer->s_train_line_3_layer, GColorBlack);
  text_layer_set_text_alignment(trainLayer->s_train_line_3_layer, GTextAlignmentLeft);
  text_layer_set_text(trainLayer->s_train_line_3_layer, "");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(trainLayer->s_train_line_3_layer));
  
    // Create Train Line 4 Layer
  trainLayer->s_train_line_4_layer = text_layer_create(GRect(72, trainLayer->yPosition + 30, 72, 15));
  text_layer_set_background_color(trainLayer->s_train_line_4_layer, GColorClear);
  text_layer_set_text_color(trainLayer->s_train_line_4_layer, GColorBlack);
  text_layer_set_text_alignment(trainLayer->s_train_line_4_layer, GTextAlignmentRight);
  text_layer_set_text(trainLayer->s_train_line_4_layer, "");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(trainLayer->s_train_line_4_layer));
  
}



void updateTrainLayer( struct TrainLayers *trainLayer, char train_destinationstation_buffer[32], char train_via_buffer[32], char train_scheduled_departure_buffer[32],
                      char train_expected_departure_buffer[32],
                      char train_platform_buffer[32] );

void updateTrainLayer( struct TrainLayers *trainLayer, char train_destinationstation_buffer[32], char train_via_buffer[32], char train_scheduled_departure_buffer[32], 
                      char train_expected_departure_buffer[32],
                      char train_platform_buffer[32] )
{
  

  
  
    // Train 1 Line 1
  snprintf(trainLayer->train_line_1_buffer_formatted, sizeof(trainLayer->train_line_1_buffer_formatted), "%s to %s", train_scheduled_departure_buffer, train_destinationstation_buffer);
  text_layer_set_text(trainLayer->s_train_line_1_layer, trainLayer->train_line_1_buffer_formatted);
  
   // Train 1 Line 2
  snprintf(trainLayer->train_line_2_buffer_formatted, sizeof(trainLayer->train_line_2_buffer_formatted), "%s", train_via_buffer);
  text_layer_set_text(trainLayer->s_train_line_2_layer, trainLayer->train_line_2_buffer_formatted);

  // Train 1 Line 3
  snprintf(trainLayer->train_line_3_buffer_formatted, sizeof(trainLayer->train_line_3_buffer_formatted), "%s", train_expected_departure_buffer);
  text_layer_set_text(trainLayer->s_train_line_3_layer, trainLayer->train_line_3_buffer_formatted);

  // Train 1 Line 4
  snprintf(trainLayer->train_line_4_buffer_formatted, sizeof(trainLayer->train_line_4_buffer_formatted), "Platform: %s", train_platform_buffer);
  text_layer_set_text(trainLayer->s_train_line_4_layer, trainLayer->train_line_4_buffer_formatted);
  
}

void destroyTrainLayer( struct TrainLayers *trainLayer);

void destroyTrainLayer( struct TrainLayers *trainLayer){
  text_layer_destroy(trainLayer->s_train_line_1_layer);
  text_layer_destroy(trainLayer->s_train_line_2_layer);
  text_layer_destroy(trainLayer->s_train_line_3_layer);
  text_layer_destroy(trainLayer->s_train_line_4_layer);
}

*/

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
  
  // Get weather update every 30 minutes
  if(tick_time->tm_sec % 30 == 0) {
  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);

  // Send the message!
  app_message_outbox_send();
}
}

static void main_window_load(Window *window) {
 // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 0, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
  // Create Departure Station Layer
  s_departure_station_layer = text_layer_create(GRect(0, 50, 144, 20));
  text_layer_set_background_color(s_departure_station_layer, GColorBlack);
  text_layer_set_text_color(s_departure_station_layer, GColorWhite);
  text_layer_set_text_alignment(s_departure_station_layer, GTextAlignmentCenter);
  text_layer_set_text(s_departure_station_layer, "Loading...");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_departure_station_layer));
  
  // Create Filter Station Layer
  s_filter_station_layer = text_layer_create(GRect(0, 70, 144, 14));
  text_layer_set_background_color(s_filter_station_layer, GColorClear);
  text_layer_set_text_color(s_filter_station_layer, GColorBlack);
  text_layer_set_text_alignment(s_filter_station_layer, GTextAlignmentLeft);
  text_layer_set_text(s_filter_station_layer, "");
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_filter_station_layer));
  
  
    // Create Divider Line
  s_divider_line_1_layer = text_layer_create(GRect(0, 86, 144, 2));
  text_layer_set_background_color(s_divider_line_1_layer, GColorBlack);
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_divider_line_1_layer));
  
  // Add train departure details
  trainLayer1.yPosition = 85;
  setupTrainLayer(&trainLayer1, window);
}

static void main_window_unload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(s_time_layer);
  
    // Destroy train elements
    text_layer_destroy(s_train1_layer);
    text_layer_destroy(s_departure_station_layer);
    text_layer_destroy(s_filter_station_layer);
    text_layer_destroy(s_divider_line_1_layer);

    destroyTrainLayer(&trainLayer1);
}


// APPMESSAGE Callbacks

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
// Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case KEY_STATION:
      snprintf(station_buffer, sizeof(station_buffer), "%s", t->value->cstring);
      break;
    case KEY_DEPARTURETIME:
      snprintf(departureTime_buffer, sizeof(departureTime_buffer), "%s", t->value->cstring);
      break;
    case KEY_FILTER_STATION:
      snprintf(station_filter_buffer, sizeof(station_filter_buffer), "%s", t->value->cstring);
      break;
    case KEY_TRAIN_DESTINATION_STATION:
      snprintf(train_destinationstation_buffer, sizeof(train_destinationstation_buffer), "%s", t->value->cstring);
      break;
    case KEY_TRAIN_VIA:
      snprintf(train_via_buffer , sizeof(train_via_buffer ), "%s", t->value->cstring);
      break;
    case KEY_SCHEDULED_DEPARTURE:
      snprintf(train_scheduled_departure_buffer , sizeof(train_scheduled_departure_buffer ), "%s", t->value->cstring);
      break;
    case KEY_EXPECTED_DEPARTURE:
      snprintf(train_expected_departure_buffer , sizeof(train_expected_departure_buffer ), "%s", t->value->cstring);
      break;
    case KEY_PLATFORM:
      snprintf(train_platform_buffer , sizeof(train_platform_buffer ), "%s", t->value->cstring);
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  
  // Departure Station
  text_layer_set_text(s_departure_station_layer, station_buffer);
  
  // Filter Station
  snprintf(station_filter_buffer_formatted, sizeof(station_filter_buffer_formatted), "Calling at %s", station_filter_buffer);
  text_layer_set_text(s_filter_station_layer, station_filter_buffer_formatted);
  
  updateTrainLayer( &trainLayer1, train_destinationstation_buffer, train_via_buffer, train_scheduled_departure_buffer, train_expected_departure_buffer,
                      train_platform_buffer );
  
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Make sure the time is displayed from the start
  update_time();
  
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
    // Destroy Window
    window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

