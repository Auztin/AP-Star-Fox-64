all: enum_gen.last

DATA:= $(shell find ../ap/data -type f -name '*.py')
enum_gen.last: enum_gen.py $(DATA) ../ap/options.py ../ap/version.py
	python $<
	touch $@

.PHONY: clean
clean:
	$(RM) enum_gen.last
