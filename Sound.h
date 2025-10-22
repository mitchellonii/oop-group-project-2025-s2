#ifndef MUSICTRACK_H
#define MUSICTRACK_H

#include <SFML/Audio.hpp>
#include <string>

class MusicTrack {
 public:
  MusicTrack();
  ~MusicTrack();

  bool openFromFile(const std::string& filepath);

  void play();
  void pause();
  void stop();

  void setLoop(bool loop);
  bool getLoop() const;

  void setVolume(float volume);
  float getVolume() const;

  void setPitch(float pitch);
  float getPitch() const;

  sf::Vector3f getPosition() const;

  void setPlayingOffset(sf::Time offset);
  sf::Time getPlayingOffset() const;

  sf::Time getDuration() const;

 private:
  sf::Music music;
};
#endif
