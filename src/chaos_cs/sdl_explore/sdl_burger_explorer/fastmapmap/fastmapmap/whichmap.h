
#define HENON x_ = 1 - c1*x*x + y; y_ = c2*x;
#define HENONSUF "_henon"
#define BURGER x_ = c1*x - y*y; y_ = c2*y + x*y;
#define BURGERSUF "_burger"


#define MAPEXPRESSION BURGER
#define MAPSUFFIX BURGERSUF


#define SAVESFOLDER ("saves" MAPSUFFIX  )
#define MAPDEFAULTFILE ("saves" MAPSUFFIX "/default.cfg" )

#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define MAPEXPRESSIONTEXT STRINGIFY(MAPEXPRESSION)
