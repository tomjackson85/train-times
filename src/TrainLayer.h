#pragma once

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
  
void setupTrainLayer( struct TrainLayers *trainLayer, Window *window );

void updateTrainLayer( struct TrainLayers *trainLayer, char train_destinationstation_buffer[32], char train_via_buffer[32], char train_scheduled_departure_buffer[32],
                      char train_expected_departure_buffer[32],
                      char train_platform_buffer[32] );

void destroyTrainLayer( struct TrainLayers *trainLayer);