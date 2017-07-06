/* */

shaftR = 5.1 / 2;
lockR = 30.0 / 2;
thickness = 5;

module myLock( )
{
    difference( ) 
    {
        cylinder( thickness, lockR, lockR, $fn = 100, center = true );
        cylinder( thickness + 1, shaftR, shaftR, $fn = 100, center = true );
        // Make teeth
        for( i=[0:3] )
        {
            rotate( [ 0, 0, 90*i ] ) 
            {
                translate([3*lockR/4, 0, 0]) {  cube(lockR/2, center=true ); }
            }
        }
    }
}

// Create 16 locks.
N = 4;
for( j = [0:N-1] )
{
    xshift = 2 * (1 + lockR) * j;
    for( k = [0:N-1] )
    {
        yshift = 2 * (1 + lockR) * k;
        translate( [xshift,yshift,0] ) myLock( );
    }
}
