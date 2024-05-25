#include "../inc/cvol.hpp"
#include "../inc/log.hpp"
#include <alsa/asoundlib.h>
#include <cmath>
#include <string>

volumeController::volumeController() {

  snd_mixer_open(&h_mixer, 1);
  snd_mixer_attach(h_mixer, card.c_str());
  snd_mixer_selem_register(h_mixer, NULL, NULL);
  snd_mixer_load(h_mixer);
  snd_mixer_selem_id_alloca(&sid);
  snd_mixer_selem_id_set_index(sid, 0);
  snd_mixer_selem_id_set_name(sid, selem_name.c_str());

  elem = snd_mixer_find_selem(h_mixer, sid);

  snd_mixer_selem_get_playback_volume_range(elem, &min_vol, &max_vol);
  logln("Initialized volume controller.");
}

volumeController::~volumeController() { snd_mixer_close(h_mixer); }

void volumeController::setVolume(long volume) {
  if (volume < 0 or volume > 100) {
    errorForce("Dangerous volume value was given: " + std::to_string(volume));
  }
  snd_mixer_selem_set_playback_volume_all(elem, volume * max_vol / 100);
  logln("Volume set to: " + std::to_string(volume));
}

long volumeController::getVolume() {
  long vol;
  snd_mixer_selem_get_playback_volume(elem, CHANNEL, &vol);
  return ceil((float)100 * vol / max_vol);
}
