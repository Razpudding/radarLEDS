#define a4 NOTE_A4
#define b4 NOTE_B4
#define fs4 NOTE_FS4

#define c5 NOTE_C5
#define cs5 NOTE_CS5
#define d5 NOTE_d5
#define e5 NOTE_E5
#define fs5 NOTE_FS5
#define g5 NOTE_g5
#define a5 NOTE_A5
#define as5 NOTE_AS5
#define b5 NOTE_B5

#define c6 NOTE_C6
#define g6 NOTE_G6
#define a6 NOTE_A6
#define as6 NOTE_AS6
#define b6 NOTE_B6

#define c7 NOTE_C7

#define sh 32 // 1/32 of a whole note
#define sn 16
#define no 8
#define me 4
#define lo 2
#define xlo 1 // 1 whole note
#define xxlo 102 // 2 whole notes
#define xxxlo 104 // 4 whole notes

//This is a rest note. My code crashes if I use 0 but anything under 20 is not hearable anyway
int r = 1;
int radarMelody[] = {
  //I've been driving all night my hands wet on the wheel
  b4, b4, cs5, cs5, b4,
  a4, fs4, fs4, fs4, fs4, fs4, a4
  , r, //temporary, remove later
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
  //I've been driving all night my hands wet on the wheel
  no, no, me, no, me,
  no, no, me, no, me, no, lo
  , xlo, //temporary, remove later
  
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
