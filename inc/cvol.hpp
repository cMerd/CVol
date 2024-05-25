#pragma once

#include <alsa/asoundlib.h>
#include <string>

class volumeController {
public:
  volumeController();

  // This function takes the volume between 0 and 100
  void setVolume(long volume);

  // This function gives the volume between 0 and 100
  long getVolume();

  ~volumeController();

private:
  long min_vol, max_vol;

  // All used variables from alsalib
  snd_mixer_t *handle;
  snd_mixer_t *h_mixer;
  snd_mixer_selem_id_t *sid;
  snd_mixer_elem_t *elem;
  const snd_mixer_selem_channel_id_t CHANNEL = SND_MIXER_SCHN_FRONT_LEFT;

  const std::string card = "default";
  const std::string selem_name = "Master";
};
