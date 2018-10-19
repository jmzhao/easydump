SUBDIRS = test src

.PHONY: all clear $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) all -C $@

clean:
	for D in $(SUBDIRS); do \
		make clean -C $$D; \
	done
