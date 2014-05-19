subdirs := src
.PHONY: all $(subdirs)
all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@

clean:
	rm -rf ./bin/* ./src/*.o
