SUBDIRS = test src

.PHONY: all clear $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) all -C $@ 

clear:
	for D in $(SUBDIRS); do \
		make clear -C $$D; \
	done
