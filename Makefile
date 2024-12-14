TARGET = esme-gpio-toggle
SRCS = esme-gpio-toggle.c
OBJS = $(SRCS:.c=.o)

CFLAGS += $(shell pkg-config --cflags libgpiod)
LDLIBS += $(shell pkg-config --libs libgpiod)

INSTALL_DIR ?= ./.install

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)

install: $(TARGET)
	mkdir -p $(INSTALL_DIR)/usr/bin
	cp $(TARGET) $(INSTALL_DIR)/usr/bin/
	mkdir -p $(INSTALL_DIR)/etc/init.d
	cp esme-gpio26-toggle $(INSTALL_DIR)/etc/init.d/
	chmod 0755 $(INSTALL_DIR)/etc/init.d/esme-gpio26-toggle

clean:
	rm -f $(OBJS) $(TARGET)
