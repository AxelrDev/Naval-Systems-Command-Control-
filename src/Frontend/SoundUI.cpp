#include "SoundUI.hpp"

void SoundUI::play(std::string sounID) {
	if (!buffer.loadFromFile("assets/music/"+sounID)) {
		std::cout << "Error al cargar el archivo de sonido." << std::endl;
	}

	sound.setBuffer(buffer);
	sound.play();
}

void SoundUI::stop() {
    sound.stop();
}