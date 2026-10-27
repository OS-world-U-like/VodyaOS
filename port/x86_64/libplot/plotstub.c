/*
 * Minimal libplot replacement (see README in port/x86_64).
 * The V7 distribution shipped libplot as prebuilt PDP-11 archives;
 * these weak no-op entry points let the portable front ends link.
 */
#pragma weak openvt
#pragma weak closevt
#pragma weak openpl
#pragma weak closepl
#pragma weak erase
#pragma weak space
#pragma weak move
#pragma weak cont
#pragma weak dot
#pragma weak point
#pragma weak line
#pragma weak linemod
#pragma weak label
#pragma weak arc
#pragma weak circle
#pragma weak box
#pragma weak plot
#pragma weak color
#pragma weak fill
int openvt() { return 0; }
int closevt() { return 0; }
int openpl() { return 0; }
int closepl() { return 0; }
int erase() { return 0; }
int space() { return 0; }
int move() { return 0; }
int cont() { return 0; }
int dot() { return 0; }
int point() { return 0; }
int line() { return 0; }
int linemod() { return 0; }
int label() { return 0; }
int arc() { return 0; }
int circle() { return 0; }
int box() { return 0; }
int plot() { return 0; }
int color() { return 0; }
int fill() { return 0; }
