#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gpiod.h>
#include <string.h>

#define DEFAULT_GPIO 26

int main(int argc, char **argv) {
    int gpio_num = DEFAULT_GPIO;
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int value = 0;

    if (argc > 2 && strcmp(argv[1], "--gpio") == 0) {
        gpio_num = atoi(argv[2]);
    }

    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        perror("Open chip failed");
        return 1;
    }

    line = gpiod_chip_get_line(chip, gpio_num);
    if (!line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        return 1;
    }

    if (gpiod_line_request_output(line, "esme-gpio-toggle", 0) < 0) {
        perror("Request line as output failed");
        gpiod_line_release(line);
        gpiod_chip_close(chip);
        return 1;
    }

    while (1) {
        if (gpiod_line_set_value(line, value) < 0) {
            perror("Set line output failed");
            break;
        }
        value = !value;
        sleep(1);
    }

    gpiod_line_release(line);
    gpiod_chip_close(chip);
    return 0;
}
