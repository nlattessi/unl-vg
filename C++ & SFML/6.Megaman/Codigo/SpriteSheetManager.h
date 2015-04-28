#ifndef SPRITESHEETMANAGER_H
#define SPRITESHEETMANAGER_H
#include <vector>
#include <SFML/Graphics.hpp>

//Para poder utilizar la instancia estatica
#include "TextureManager.h"

//Para uso con clase FRAME y carga desde un archivo .json
#include "Frame.h"
#include "Jzon.h"

class SpriteSheetManager
{
	public:

		// carga un sprite sheet
		void Load(std::string filename, unsigned nCols, unsigned nRows=1);
		// devuelve la imagen en la posicion i
		sf::IntRect &GetRect(unsigned i);
		//sf::IntRect &operator[](unsigned i);
		// devuelve la cantidad de imagenes almacenadas
		unsigned Size();

		// Carga un sf::IntRect individual
		void pushRect(sf::IntRect r);
	
		//Para uso con clase FRAME y carga desde un archivo .json
		void pushFrame( Frame frame );
		Frame &getFrame( unsigned i );
		void loadFromJson( std::string filename );
		Frame &operator[](unsigned i);

	private:
		std::vector<sf::IntRect> rects;
	
		//Para uso con clase FRAME y carga desde un archivo .json
		std::vector<Frame> frames;
};

#endif