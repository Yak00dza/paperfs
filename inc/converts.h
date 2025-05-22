#ifndef CONVERTS_H
#define CONVERTS H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//paper properties
#define DPI 300
#define A4_INCH_WIDTH 8.27
#define A4_INCH_HEIGHT 11.69

#define LEFT_MARGIN 0.3 //inches
#define RIGHT_MARGIN 0.3 //inches
#define TOP_MARGIN 0.3 //inches
#define BOTTOM_MARGIN 0.3 //inches

//program configs
#define BAR_WIDTH 0.05 //inches
#define BAR_HEIGHT 0.08 //inches
#define DISTANCE_BETWEEN_BARS 0.03 //inches
#define DISTANCE_BETWEEN_LINES 0.1

typedef struct {
	int x;
	int y;
} point;

typedef struct {
	int paper_width;
	int paper_height;

	int bar_width;
	int bar_height;
	int bar_distance;
	int line_gap;

	int byte_width;	

	int bytes_per_line;
	int max_lines;

	point start_pixel;

} properties_t;

FILE *file_to_image(FILE* file, char* output_file_name);
FILE *save_pixels_to_pbm(uint8_t *pixels, char *output_name, properties_t *properties);

void setup_properties(properties_t *properties);

void calculate_resolution(properties_t *properties);
void calculate_bar_properties(properties_t *properties);
void calculate_bytes_per_line(properties_t *properties);
void calculate_max_lines(properties_t *properties);
void calculate_start_pixel(properties_t *properties);

void write_byte_to_pixels(uint8_t byte, uint8_t *pixels, int line_n, int byte_n, properties_t *properties);

#endif
