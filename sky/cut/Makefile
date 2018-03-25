
output = \
	top.svg \
	middle.svg \
	bottom.svg \
	side.svg \

all: $(output)

%.svg: %.scad
	openscad $^ -o $@
	svg-dimension-to-mm $@ $@

%.scad: parts/base.scad
	echo "include <$^>" > $@
	echo "$(basename $@)();" >> $@

clean:
	rm -rf $(output)

