all : ./encoder_wheel.png ./encoder_wheel.stl
	@echo "All done"


%.png : %.scad 
	openscad -o $@ $< --projection=o --colorscheme=BeforeDawn \
	    --camera=150,150,300,0,0,0

%.stl : %.scad 
	openscad -o $@ $< 
