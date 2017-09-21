/* 
 * An optical encoder with 48-32-28 slits.
 * GNU-GPLv3. (c) 2017 Dilawar Singh  <dilawars@ncbs.res.in>
 */

shaftDiameter = 6.2;
wheelDiameter = 120;
shaftMargin = 10;
shaftHeight = 20;
shaftBevel = 0;
shaftR = shaftDiameter/2;
wheelR = wheelDiameter/2;
wheelHeigh = 2; 
wheelGrooveDepth = 1;

// Outer most slit width.
slitW = 3;
slitL = 4;
gapBetweenSlits = 1;

// Outermost slits.
strip1Count = 24;
strip1OuterR = wheelR - 3;
strip1SlitL = 2 * slitL;
strip1InnerR = strip1OuterR - strip1SlitL;
strip1Width = slitW;

// Second strip 
strip2Count = 24;
strip2SlitL = slitL;
strip2OuterR = strip1InnerR - gapBetweenSlits;
strip2InnerR = strip2OuterR - strip2SlitL;
strip2Width = slitW;

// Third stip of teeth.
teethCount = 24;
teethSlitL = slitL;
teethOuterR = wheelR / 1.5;
teethInnerR = teethOuterR - teethSlitL;
teethRadius = 1;
teethHeight = 10;


union( ) {
    difference () 
    {
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
                        cube(size = [strip2Width,strip2SlitL,wheelHeigh+1], center = true);
                    }
                }
            }

        }
    }

    // Strip of teeth.
    for(i=[0:teethCount-1]) 
    {
        theta = 360/teethCount;
        rotate(a = [wheelHeigh,0,theta+(theta)*i]) 
        {
            translate( v=[0,teethInnerR+(teethSlitL/2),wheelHeigh+teethHeight/5]) 
            {
                cylinder( teethHeight,teethRadius, teethRadius, $fn = 50, center = true);
            }
        }
    }
}
