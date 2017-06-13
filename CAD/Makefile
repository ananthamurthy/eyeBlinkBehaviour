all : ./encoder_wheel.png
	@echo "All done"


%.png : %.scad 
	openscad -o $@ $< --projection=o --colorscheme=BeforeDawn \
	    --camera=300,200,200,0,0,0
	openscad -o $@.2.png $< --projection=o --colorscheme=BeforeDawn \
	    --camera=0,0,300,0,0,0

%.stl : %.scad 
	openscad -o $@ $< 
