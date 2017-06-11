all : ./encoder_wheel.png ./encoder_wheel.stl ./lock.png ./lock.stl
	@echo "All done"


%.png : %.scad 
	openscad -o $@ $< --projection=o --colorscheme=BeforeDawn \
	    --camera=300,200,200,0,0,0

%.stl : %.scad 
	openscad -o $@ $< 
