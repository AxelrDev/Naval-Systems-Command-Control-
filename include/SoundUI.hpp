#ifndef SOUNDUI_HPP
#define SOUNDUI_HPP
#include <SFML/Audio.hpp>
#include <iostream>
class SoundUI
{
public:
	sf::SoundBuffer buffer;
	sf::Sound sound;

	void play(std::string soundID);
    void stop();
};

#endif
