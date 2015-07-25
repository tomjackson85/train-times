#include <pebble.h>
#include "TrainLayer.h"

void setupTrainLayer( struct TrainLayers *trainLayer, Window *window )
{
  
  
   // Create Train Line 1 Layer
  trainLayer->s_train_line_1_layer = text_layer_create(GRect(0, trainLayer->yPosition, 144, 15));
  text_layer_set_background_color(trainLayer->s_train_line_1_layer, GColorClear);
  text_layer_set_text_color(trainLayer->s_train_line_1_layer, GColorBlack);
  text_layer_set_text_alignment(trainLayer->s_train_line_1_layer, GTextAlignmentLeft);
  text_layer_set_text(trainLayer->s_train_line_1_layer, "");
  
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

void updateTrainLayerForTrain( struct TrainLayers *trainLayer, struct Train *train ){
    updateTrainLayer(trainLayer, train->train_destinationstation, train->train_via, train->train_scheduled_departure,
                     train->train_expected_departure, train->train_platform);
}


void destroyTrainLayer( struct TrainLayers *trainLayer){
  text_layer_destroy(trainLayer->s_train_line_1_layer);
  text_layer_destroy(trainLayer->s_train_line_2_layer);
  text_layer_destroy(trainLayer->s_train_line_3_layer);
  text_layer_destroy(trainLayer->s_train_line_4_layer);
}


