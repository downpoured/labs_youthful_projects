
#include "common.h"

#define DrawModePhase 1
#define DrawModeColorLine 2
#define DrawModeColorDisk 3
#define DrawModeBasinsDistance 10
#define DrawModeBasinsX 11
#define DrawModeBasinsDifference 12
#define DrawModeBasinsQuadrant 13
#define DrawModeEscapeTimeLines 20
#define DrawModeEscapeTime 21

enum {
  maskOptionsDiagramMethod = 0xf0000000, //Diagram is lyapunov or countpixels
  maskOptionsDiagramColoring = 0x0f000000, //Diagram is hsl or black/white
  maskOptionsBasinColor = 0x00f00000, //Basin colors include blue.
  maskOptionsQuadrantContrast = 0x000f0000, //Contrast in quadrants.
  maskOptionsEscapeFillIn = 0x0000f000, //Fill in basin when in escapetime mode.
  maskOptionsColorShowJustOneLine = 0x00000f00 //when in color mode, show just one line.

} ;

void DrawFigure( SDL_Surface* pSurface, double c1, double c2, int width ) ;
void renderLargeFigure( SDL_Surface* pSurface, int width, const char* filename ) ;

#define ISTOOBIG(x) ((x)<-1e2 || (x)>1e2)
#define ISTOOBIGF(x) ((x)<-1e2f || (x)>1e2f)
//floating point comparison. see also <float.h>'s DBL_EPSILON and DBL_MIN. 1e-11 also ok.
#define VERYCLOSE(x1,x2) (fabs((x1)-(x2))<1e-8)

#ifdef _MSC_VER //using Msvc
#include <float.h>
#define ISFINITE(x) (_finite(x))
#else
#define ISFINITE(x) (isfinite(x))
#endif
