SCHEMATICS := controller.sch driver.sch

.PHONY: all clean fab

all: $(SCHEMATICS:.sch=.bom) $(SCHEMATICS:.sch=.png) fab

clean:
	-rm -f *.bak *.bak0 *.bak1 *.pcb\- *.sch\~

%.bom: %.sch
	gnetlist -g partslist3 -o $@ -- $<
	column -t -s'	' $@ > $@.tmp
	mv $@.tmp $@

%.png: %.sch
	gaf export -c -s auto -o $@ -- $<

fab:
	mkdir -p fab
	$(foreach s,$(SCHEMATICS:.sch=.pcb),pcb -x gerber $(s);)
	mv *.gbr *.cnc fab/
