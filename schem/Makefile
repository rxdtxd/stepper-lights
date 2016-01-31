# TODO: just look at it!
bom:
	gnetlist -g partslist3 -o controller.bom controller.sch
	column -t controller.bom > tmp.bom
	mv tmp.bom controller.bom
	gnetlist -g partslist3 -o driver.bom driver.sch
	column -t driver.bom > tmp.bom
	mv tmp.bom driver.bom
