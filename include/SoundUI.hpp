#ifndef SOUNDUI_HPP
#define SOUNDUI_HPP

/**
 * @file SoundUI.hpp
 * @brief Declares the SoundUI class for handling sound playback in the game.
 */

#include <SFML/Audio.hpp>
#include <iostream>

/**
 * @class SoundUI
 * @brief Manages sound playback using SFML's audio system.
 */
class SoundUI {
public:
    sf::SoundBuffer buffer; ///< Buffer that holds audio data
    sf::Sound sound;        ///< Sound instance that plays audio from the buffer

    /**
     * @brief Plays a sound associated with a given sound identifier.
     * @param soundID Identifier for the sound file to load and play.
     */
    void play(std::string soundID);

    /**
     * @brief Stops the currently playing sound.
     */
    void stop();
};

#endif // SOUNDUI_HPP