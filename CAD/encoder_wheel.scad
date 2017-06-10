/* 
 * An optical encoder with 48-32-28 slits.
 * GNU-GPLv3. (c) 2017 Dilawar Singh  <dilawars@ncbs.res.in>
 */

shaftDiameter = 5.1;
wheelDiameter = 120;
shaftMargin = 10;
shaftHeight = 20;
shaftBevel = 0;
shaftR = shaftDiameter/2;
wheelR = wheelDiameter/2;
wheelHeigh = 2; 
wheelGrooveDepth = 1;

// Outer most slit width.
slitW = 1.5;
slitL = 4;
gapBetweenSlits = 1;

// Outermost slits: 48 in numbers.
strip1Count = 48;
strip1OuterR = wheelR - 3;
strip1SlitL = 2 * slitL;
strip1InnerR = strip1OuterR - strip1SlitL;
strip1Width = slitW;

// Second strip : 32
strip2Count = 48;
strip2SlitL = slitL;
strip2OuterR = strip1InnerR - gapBetweenSlits;
strip2InnerR = strip2OuterR - strip2SlitL;
strip2Width = slitW;

difference () {
    rotate_extrude($fn=200) 
        polygon( points=[ [shaftR,0],[wheelR,0]
                ,[wheelR-wheelGrooveDepth,wheelHeigh/2]
                ,[wheelR,wheelHeigh]
                ,[shaftR+shaftMargin,wheelHeigh]
                ,[shaftR+shaftMargin,shaftHeight]
                ,[shaftR+shaftBevel,shaftHeight]
                ,[shaftR,shaftHeight-shaftBevel] 
            ] 
        );

    union() 
    {
        // Strip 1
        for(i=[0:strip1Count-1]) 
        {
            rotate(a = [0,0,(360/strip1Count)*i]) 
            {
                translate( v=[0,strip1InnerR+(strip1SlitL/2),wheelHeigh/2]) 
                {
                    cube(size = [strip1Width,strip1SlitL,wheelHeigh+1] ,center = true);
                }
            }
        }

        // Strip 2.
        for(i=[0:strip2Count-1]) 
        {
            theta = 360/strip2Count;
            rotate(a = [0,0,(3*theta/4)+(theta)*i]) 
            {
                translate( v=[0,strip2InnerR+(strip2SlitL/2),wheelHeigh/2]) 
                {
                    cube(size = [strip2Width,strip2SlitL,wheelHeigh+1] ,center = true);
                }
            }
        }

        /*
        // Strip 3.
        for(i=[0:strip3Count-1]) 
        {
            rotate(a = [0,0,(360/strip3Count)*i]) 
            {
                translate( v=[0,strip3InnerR+(strip3SlitL/2),wheelHeigh/2]) 
                {
                    cube(size = [strip3Width,strip3SlitL,wheelHeigh+1] ,center = true);
                }
            }
        }

        // Strip 4.
        for(i=[0:strip4Count-1]) 
        {
            rotate(a = [0,0,(360/strip4Count)*i]) 
            {
                translate( v=[0,strip4InnerR+(strip4SlitL/2),wheelHeigh/2]) 
                {
                    cube(size = [strip4Width,slitL,wheelHeigh+1],center = true);
                }
            }
        }
        */

        // End of strips
    }
}
