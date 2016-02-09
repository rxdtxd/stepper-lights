SCHEMATICS := controller driver

.PHONY: all
all: bom gerber

.PHONY: bom
bom:
	$(foreach s,$(SCHEMATICS),gnetlist -g partslist3 -o $(s).bom $(s).sch;)
	$(foreach s,$(SCHEMATICS),column -t -s'	' $(s).bom > $(s).tmp;)
	$(foreach s,$(SCHEMATICS),mv $(s).tmp $(s).bom;)

.PHONY: clean
clean:
	rm -f *.bak *.bak0 *.bak1 *.pcb\- *.sch\~

.PHONY: gerber
gerber:
	$(foreach s,$(SCHEMATICS),pcb -x gerber $(s).pcb;)
	mv *.gbr *.cnc fab/
