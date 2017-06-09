// All units are in mm.
// Modified from Thingyverse.

shaftDiameter = 5.1;
wheelDiameter = 120;
shaftMargin = 10;
shaftHeight = 20;
shaftBevel = 0;

// 3x of this value
wheelHeigh = 2;
wheelGrooveDepth = 1;

encoderInnerRadius = 44;
encoderOuterRadius = 52;
encoderSlitWidth = 1;
encoderSlitMargin = 1;
encoderSlitCount = 32;

encoderInnerRadiusF = 55;
encoderOuterRadiusF = 58;
encoderSlitWidthF = 1;
encoderSlitCountF = 48;

shaftR = shaftDiameter/2;
wheelR = wheelDiameter/2;

encoderSlitLength = encoderOuterRadius-encoderInnerRadius;
encoderSlitLengthF = encoderOuterRadiusF-encoderInnerRadiusF;

difference () {
	rotate_extrude($fn=200) 
    polygon( points=[ 
        [shaftR,0],[wheelR,0]
        ,[wheelR-wheelGrooveDepth,wheelHeigh/2]
        ,[wheelR,wheelHeigh]
        ,[shaftR+shaftMargin,wheelHeigh]
        ,[shaftR+shaftMargin,shaftHeight]
        ,[shaftR+shaftBevel,shaftHeight]
        ,[shaftR,shaftHeight-shaftBevel]] 
    );
	
	union() {
		for(i=[0:encoderSlitCount-1]) 
        {
			rotate(a = [0,0,(360/encoderSlitCount)*i]) 
            {
				translate(
                    v=[0,encoderInnerRadius+(encoderSlitLength/2),wheelHeigh/2]
                    ) {
                            cube(size = [encoderSlitWidth,encoderSlitLength,wheelHeigh+1]
                                    ,center = true
                        );
                    }
               }
		}
        
        
        for(i=[0:encoderSlitCountF-1]) 
        {
			rotate(a = [0,0,(360/encoderSlitCountF)*i]) 
            {
				translate(
                    v=[0,encoderInnerRadiusF+(encoderSlitLengthF/2),wheelHeigh/2]
                    ) {
                            cube( size = [ 
                                    encoderSlitWidthF,encoderSlitLengthF,wheelHeigh+1]
                                    , center = true
                                );
                    }
               }
		}
        
	}
}
