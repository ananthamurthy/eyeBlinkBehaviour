// All units are in mm.
shaftDiameter = 6.0;
wheelDiameter = 120;
shaftMargin = 10;
shaftHeight = 10;
shaftBevel = 0.5;

// 3x of this value
wheelHeigh = 1;
wheelGrooveDepth = 1;

encoderInnerRadius = 45;
encoderOuterRadius = 55;
encoderSlitWidth = 1;
encoderSlitMargin = 1;
encoderSlitCount = 64;

shaftR = shaftDiameter/2;
wheelR = wheelDiameter/2;

encoderSlitLength = encoderOuterRadius-encoderInnerRadius;

difference () {

	rotate_extrude($fn=200) polygon( points=[[shaftR,0],[wheelR,0],[wheelR-wheelGrooveDepth,wheelHeigh/2],[wheelR,wheelHeigh],[shaftR+shaftMargin,wheelHeigh],[shaftR+shaftMargin,shaftHeight],[shaftR+shaftBevel,shaftHeight],[shaftR,shaftHeight-shaftBevel]] );
	
	union() {
		for(i=[0:encoderSlitCount-1]) {
			rotate(a = [0,0,(360/encoderSlitCount)*i]) {
				translate(v=[0,encoderInnerRadius+(encoderSlitLength/2),wheelHeigh/2]) {
					cube(size = [encoderSlitWidth,encoderSlitLength,wheelHeigh+1],center = true);
				}
			}
		}
	}
}
