subdirs := Sim Vis
.PHONY: all $(subdirs)
all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@

clean:
	rm -rf ./Sim/bin/* ./Sim/src/*.o ./Vis/bin/*
