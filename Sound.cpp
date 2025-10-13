#include "Sound.h"

#include <iostream>

MusicTrack::MusicTrack() : music() {}

MusicTrack::~MusicTrack() {}

bool MusicTrack::openFromFile(const std::string& filepath) {
  if (!music.openFromFile(filepath)) {
    std::cerr << "[MusicTrack] ERROR: Could not open music file: " << filepath
              << "\n";
    return false;
  }
  return true;
}

void MusicTrack::play() { music.play(); }
void MusicTrack::pause() { music.pause(); }
void MusicTrack::stop() { music.stop(); }

void MusicTrack::setLoop(bool loop) { music.setLooping(loop); }

void MusicTrack::setVolume(float volume) { music.setVolume(volume); }
float MusicTrack::getVolume() const { return music.getVolume(); }

void MusicTrack::setPitch(float pitch) { music.setPitch(pitch); }
float MusicTrack::getPitch() const { return music.getPitch(); }

sf::SoundSource::Status MusicTrack::getStatus() const {
  return music.getStatus();
}

void MusicTrack::setPlayingOffset(sf::Time offset) {
  music.setPlayingOffset(offset);
}
sf::Time MusicTrack::getPlayingOffset() const {
  return music.getPlayingOffset();
}

sf::Time MusicTrack::getDuration() const { return music.getDuration(); }
