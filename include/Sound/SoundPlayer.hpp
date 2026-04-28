#ifndef SOUNDPLAYER_HPP
#define SOUNDPLAYER_HPP

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <list>

enum SoundType {
    HOVER = 1,
    SELECT = 2
};

class SoundPlayer {
private:
    std::unordered_map<SoundType, sf::SoundBuffer> buffers;
    std::vector<std::pair<SoundType, sf::Sound>> activeSounds;

public:
    SoundPlayer() = default;

    bool loadSound(const std::string& path, const SoundType key);
    void playSound(const SoundType key);
    void stopAll();
};

#endif