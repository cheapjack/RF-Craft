SVGFILES := $(wildcard *.svg)

all: $(SVGFILES:%.svg=%.eps)

%.eps : %.svg
	inkscape -E $*.eps $*.svg

clean:
	rm *.eps
