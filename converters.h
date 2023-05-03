/*
 * Function converting hsv to rgb
 * @parameters int hue, int saturation, int value
 * @output unsigned int with blue color in the first byte,
 *   green color in the second byte, and red color in the third byte
 *  Reference:
 * https://www.youtube.com/watch?v=m5tEk-87wnA&list=PLQL6z4JeTTQkguL75-cpr6tXc6atfm5m3&index=10
 */
unsigned int hsv2rgb(int hue, int saturation, int value);

/*
 * Function converting hsv to rgb for lcd display
 * @parameters int hue, int saturation, int value
 * @output unsigned int with blue color in the first byte,
 *   green color in the second byte, and red color in the third byte
 *  Reference:
 * https://www.youtube.com/watch?v=m5tEk-87wnA&list=PLQL6z4JeTTQkguL75-cpr6tXc6atfm5m3&index=10
 */
unsigned int hsv2rgb_lcd(int hue, int saturation, int value);
