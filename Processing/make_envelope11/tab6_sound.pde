import processing.sound.*;

AudioSample sample;

void sound_preview() {

  int resolution = 4410;
  float[] sinewave = new float[resolution];

  


  for (int i = 0; i < wavedata_f.length; i++) {
    sinewave[i] = wavedata_f[i]*0.1;
  }
  sample = new AudioSample(this, sinewave, 8000);

  sample.amp(0.1);
  sample.play();
}
