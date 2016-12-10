#define a4 NOTE_A4
#define b4 NOTE_B4
#define fs4 NOTE_FS4

#define c5 NOTE_C5
#define cs5 NOTE_CS5
#define d5 NOTE_d5
#define e5 NOTE_E5
#define fs5 NOTE_FS5
#define g5 NOTE_G5
#define gs5 NOTE_GS5
#define a5 NOTE_A5
#define as5 NOTE_AS5
#define b5 NOTE_B5

#define c6 NOTE_C6
#define g6 NOTE_G6
#define a6 NOTE_A6
#define as6 NOTE_AS6
#define b6 NOTE_B6

#define c7 NOTE_C7

//#define sh 32 // 1/32 of a whole note
//#define sn 16
//#define no 8
//#define me 4
//#define lo 2
//#define xlo 1 // 1 whole note
//#define xxlo 102 // 2 whole notes
//#define xxxlo 104 // 4 whole notes

int nLengths[] = {16, 8, 4, 2, 1, 102, 104};

int sh = nLengths[0];
int no = nLengths[1];
int me = nLengths[2];
int lo = nLengths[3];
int xlo = nLengths[4];
int xxlo = nLengths[5];
int sw = 12;    //swing note 1, damn you barry hayes
int swl = 6;  //swing note 2, see above

//This is a rest note. My code crashes if I use 0 but anything under 20 is not hearable anyway
int r = 1;
int radarMelody[] = {
  
  //I've been driving all night my hands wet on the wheel 0:47
  r, r, b4, b4, cs5, cs5, b4, a4, fs4, fs4, fs4, fs4, fs4, a4, r,
  //there's a voice 0:52
  r,r, cs5, cs5, cs5, cs5, cs5, cs5, r, cs5, cs5 , b4, a4, fs4, r,
  //My baby 0:57
  fs5, fs5, r, e5, fs5 ,fs5, fs5, fs5, a5, e5, fs5, r, r, r,
  //half post 4 1:02
  r, r, b4, cs5, b4, cs5, cs5, cs5, b4, cs5, cs5, b4, a4, fs4, r, r,
  //When she's lonely 1:07
  r, e5, e5, e5, gs5, r, gs5, fs5, e5, fs5, r, fs5, fs5, e5, fs5, r, r,
  //She sends a 1:12
  r, e5, e5, e5, gs5, r, gs5, fs5, e5, fs5 , r , r, fs5, e5, fs5, r, r,
  //don't need a 
  gs5, gs5, fs5, gs5, fs5, gs5, r, r,

  //We've got a thing and it's a called radar love
  a5, a5, a5,
  fs5, e5,
  e5, e5, e5,
  e5, e5, fs5, a5,
  r, r
  ,
  //We've got a thing in the air
  r, a5, a5, a5, fs5, r,
  cs5, cs5, cs5, b4, r, r 
  
};
int radarTempo[]{
  //I've been driving all night my hands wet on the wheel 0:47
  lo, swl, sw, swl, me, sw, me, swl, sw, me, swl, me, swl, lo, xlo,
  //there's a voice 0:52
  lo, swl, sw, swl, me, sw, swl, me, sw, me, me, me, me, me, xlo,
  //My baby 0:57
  swl, me, sw, swl, me , sw, swl, sw, me, swl, me, sw, me, xlo,
  //half post 4 1:02
  me, swl, sw, swl, sw, me, me, swl, sw, me, me, me, me, me, xlo, xlo,
  //When she's lonely 1:07
  me, me, swl, me, me, sw, me, me, swl, me, sw, me, me, swl, lo, sw, lo,
  //She sends a 1:12
  me, me, me, swl, me, sw, me, me, swl, me, sw, me, me, swl, lo, sw, lo,
   //don't need a 
  me, swl, sw, me, swl, lo, sw, lo,
  
  //We've got a thing and it's a called radar love
  me, no, me,
  me, lo,  
  no, me, lo,
  no, me, me, lo,
  me, no  
  ,
  //We've got a thing in the air
  me, me, no, me, lo, no,
  me, no, me, lo, me, no
};
