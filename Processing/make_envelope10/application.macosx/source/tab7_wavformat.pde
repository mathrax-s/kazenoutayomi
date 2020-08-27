import javax.sound.sampled.*;
import java.io.*;
AudioInputStream ais ;


void wave_export() {
  AudioFormat frmt = new AudioFormat(44100, 8, 1, true, true);
  ais = new AudioInputStream(new ByteArrayInputStream(wavedata), frmt, wavedata.length / frmt.getFrameSize() );

  try { 
    AudioSystem.write(ais, AudioFileFormat.Type.WAVE, new File(sketchPath()+"/data/test.wav"));
  } 
  catch(Exception e) {
    e.printStackTrace();
  }
}
