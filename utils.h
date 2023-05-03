/*
 * Function to compress rgb color stored in int to short, which is acknowledged
 * by lcd display
 */
unsigned short compress_rgb_color(unsigned int);

// Debug functions
void write_to_file(unsigned short *);
unsigned int decompress_rgb_color(unsigned short);
