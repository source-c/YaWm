.PHONY : all clean clean-all

DIRS := dmenu slock status utils wm

all:
	@for dir in $(DIRS); do $(MAKE) -C $$dir all; done

clean:
	@for dir in $(DIRS); do $(MAKE) -C $$dir clean; done

clean-all: clean
	@for dir in $(DIRS); do $(MAKE) -C $$dir clean-all; done
	@find . -type f \( \
		-name \*~ -o \
		-name \*.bkp \) \
		-exec rm -f \{\} \+

install: all
	@for dir in $(DIRS); do $(MAKE) -C $$dir install; done