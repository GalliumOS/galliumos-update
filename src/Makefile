#!/usr/bin/make -f

CFLAGS += -Os -Wno-unused-result

BIN = update_package_index
INSTALL_DIR = $(DESTDIR)/usr/lib/galliumos-update

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<
	strip $@

install: all
	install -d $(INSTALL_DIR)
	install -o root -g root -m 04755 $(BIN) $(INSTALL_DIR)/$(BIN)

clean:
	$(RM) $(BIN)

.PHONY: clean install all
