import ddf.minim.*;

Minim minim;
AudioSample player;

void sound_preview() {
  player.shiftVolume(0,1,100);
  player.trigger();
}
