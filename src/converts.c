#include "converts.h"

FILE *file_to_image(FILE *file, char* output_name)
{
	properties_t properties;
	setup_properties(&properties);

	uint8_t *pixels = malloc(properties.paper_width * properties.paper_height * sizeof(uint8_t));

	int n_bytes = 0;

	int current_line = 0;
	int current_byte = 0;

	int max_bytes = properties.max_lines * properties.bytes_per_line;
	
	//first line is filled with ones for calibration
	for (int i = 0; i < properties.bytes_per_line; ++i) {
		write_byte_to_pixels((uint8_t) 0xFF, pixels, 0, i, &properties);
	}
	current_line = 1;
	n_bytes += properties.bytes_per_line; 

	int byte;
	while ((byte = fgetc(file)) != EOF) {
		if (n_bytes > max_bytes) {
			return NULL; //File too big, not supported for now
		}
	
		write_byte_to_pixels((uint8_t) byte, pixels, current_line, current_byte, &properties);

		current_byte = (current_byte + 1) % properties.bytes_per_line;
		if (current_byte == 0) {
			current_line++;
		}

		n_bytes++;
	}	

	FILE *result = save_pixels_to_pbm(pixels, output_name, &properties);
	free(pixels);

	return result;
}

void write_byte_to_pixels(uint8_t byte, uint8_t *pixels, int line_n, int byte_n, properties_t *properties)
{
	int x, y;
	x = properties->start_pixel.x + byte_n * properties->byte_width;	
	y = properties->start_pixel.y + line_n * (properties->bar_height + properties->line_gap);

	uint8_t arrow = 0x80;

	uint8_t bit;
	for (int i = 0; i < 8; ++i) {
		bit = (uint8_t) ((byte & (arrow >> i)) != 0);
		for (int j = 0; j < properties->bar_height; ++j)
		{
			for (int k = 0; k < properties->bar_width; ++k) {
				pixels[x * properties->paper_height + y] = bit;
				x++;
			}
			x -= properties->bar_width;
			y++;
		}
		y -= properties->bar_height;
		x += properties->bar_width + properties->bar_distance;
	}	
}	

FILE *save_pixels_to_pbm(uint8_t *pixels, char* output_name, properties_t *properties)
{
	FILE *file = fopen(output_name, "w");
	if (!file) {
		fprintf(stderr, "Failed to open file '%s'\n", output_name);
        return NULL;
    }

	fprintf(file, "P1\n%d %d\n", properties->paper_width, properties->paper_height);

    for (int y = 0; y < properties->paper_height; ++y) {
        for (int x = 0; x < properties->paper_width; ++x) {
            fprintf(file, "%d ", pixels[x * properties->paper_height + y]);
        }
        fprintf(file, "\n");
    }
	return file;	
}

void setup_properties(properties_t *properties)
{
	calculate_resolution(properties);
	calculate_bar_properties(properties);
	calculate_bytes_per_line(properties);
	calculate_max_lines(properties);
	calculate_start_pixel(properties);
}

void calculate_resolution(properties_t *properties)
{
	properties->paper_width = (int) (DPI * A4_INCH_WIDTH);
	properties->paper_height = (int) (DPI * A4_INCH_HEIGHT);
}

void calculate_bar_properties(properties_t *properties)
{
	properties->bar_width = BAR_WIDTH * DPI;
	properties->bar_height = BAR_HEIGHT * DPI;
	properties->bar_distance = DISTANCE_BETWEEN_BARS * DPI;
	properties->line_gap = DISTANCE_BETWEEN_LINES * DPI;

	properties->byte_width = 8 * (properties->bar_width + properties->bar_distance);
}

void calculate_bytes_per_line(properties_t *properties)
{
	int usable_pixels = properties->paper_width - (int) (DPI * (LEFT_MARGIN + RIGHT_MARGIN));
	int bits_per_line = (int) ((usable_pixels + properties->bar_distance) / (properties->bar_width + properties->bar_distance));

	properties->bytes_per_line = (int) (bits_per_line / 8);	
}

void calculate_max_lines(properties_t *properties)
{
	int usable_pixels = properties->paper_height - (int) (DPI * (TOP_MARGIN + BOTTOM_MARGIN));
	properties->max_lines = (int) ((usable_pixels + properties->line_gap) / (properties->bar_height + properties->line_gap));
}

void calculate_start_pixel(properties_t *properties)
{
	properties->start_pixel.x = (int) (LEFT_MARGIN * DPI) - 1;
	properties->start_pixel.y = (int) (TOP_MARGIN * DPI) - 1;
}
