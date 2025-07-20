#ifndef state_machines_included
#define state_machines_included

enum SongState {IDLE, PLAYING};
extern enum SongState song_state;

void police_siren_led();
void play_song();
void clear();
void state_advance();

#endif //included
