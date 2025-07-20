#ifndef buzzer_included
#define buzzer_included

/* notes: period = 2,000,000 / frequency (hz) */
#define C4 7645   // 261.63 Hz
#define D4 6812   // 293.66 Hz
#define E4 6061   // 329.63 Hz
#define G4 5102   // 392.00 Hz

void buzzer_init();
void buzzer_set_period(short cycles);
void police_siren();
void mary_had_a_little_lamb();
void reset_mary_had_a_little_lamb();

extern char song_finished;

#endif // included
