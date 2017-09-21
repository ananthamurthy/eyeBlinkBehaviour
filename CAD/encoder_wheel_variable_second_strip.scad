/* 
 * An optical encoder with 48-32-28 slits.
 * GNU-GPLv3. (c) 2017 Dilawar Singh  <dilawars@ncbs.res.in>
 */

shaftDiameter = 6.5;
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

// Outermost slits: 48 in numbers.
strip1Count = 32;
strip1OuterR = wheelR - 3;
strip1SlitL = 2 * slitL;
strip1InnerR = strip1OuterR - strip1SlitL;
strip1Width = slitW;

// Second strip : 32
strip2Count = 32;
strip2SlitL = slitL;
strip2OuterR = strip1InnerR - gapBetweenSlits;
strip2InnerR = strip2OuterR - strip2SlitL;
strip2Width = slitW;

module slit( n, startangle, dtheta )
{
    for( i=[0:n-1] )
    {
        theta = startangle + i * dtheta;
        rotate(a = [0,0,theta]) 
        {
            translate( v=[0,strip2InnerR+(strip2SlitL/2),wheelHeigh/2]) 
            {
                cube(size = [strip2Width,strip2SlitL,wheelHeigh+1], center = true);
            }
        }
    }
}

module slit_group( theta, dw, n = 4 )
{
    for( i=[1:n] )
    {
        slit( i, theta+(i*(i+1)/2-1)*dw, dw );
    }
}

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
        dW = ( 180 * strip2Width / strip2OuterR / 3.1416 );
        sW = 14 * dW;
        slit_group(0, dW, 4 );
        slit_group(sW, dW, 4 );
        slit_group(2*sW, dW, 4 );
        slit_group(3*sW, dW, 4 );
        slit_group(4*sW, dW, 4 );
        slit_group(5*sW, dW, 4 );
        slit_group(6*sW, dW, 4 );

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
