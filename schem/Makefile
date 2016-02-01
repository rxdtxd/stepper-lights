REMOVE=rm -f

# TODO: just look at it!
bom:
	gnetlist -g partslist3 -o controller.bom controller.sch
	column -t -s'	' controller.bom > tmp.bom
	mv tmp.bom controller.bom
	gnetlist -g partslist3 -o driver.bom driver.sch
	column -t -s'	' driver.bom > tmp.bom
	mv tmp.bom driver.bom

clean:
	$(REMOVE) *.bak *.bak0 *.bak1 *.pcb\- *.sch\~

gerber:
	pcb -x gerber controller.pcb
	pcb -x gerber driver.pcb
	mv *.gbr *.cnc fab/
