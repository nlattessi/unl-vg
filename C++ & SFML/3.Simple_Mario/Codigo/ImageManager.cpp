#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "imageManager.h"

imageManager::imageManager() : images_(), resource_directories_() {}

imageManager::~imageManager() {
	images_.clear();
	resource_directories_.clear();
}

const sf::Texture& imageManager::getImage( const std::string& filename ) {
	// Se chequea si la imagen ya existe
	for( std::map<std::string, sf::Texture>::const_iterator it = images_.begin();
		 it != images_.end(); 
		 ++it) {

		if( filename == it->first ) {
			std::cout << "DEBUG_MESSAGE: " << filename << " usando imagen existente.\n";
			return it->second;
		}
	}
	
	// La imagen no existe, crearla y almacenarla en arreglo.
	sf::Texture image;

	// Se busca el directorio principal del proyecto.
	if( image.loadFromFile( filename ) ) {
		images_[filename] = image;
		std::cout << "DEBUG_MESSAGE: " << filename << " cargando imagen.\n";
		return images_[filename];
	}

	// Si la imagen aun no se encontr�, buscar en todos los directorios registrados.
	for( std::vector< std::string >::iterator it = resource_directories_.begin();
		 it != resource_directories_.end();
		 ++it )
	{
		if( image.loadFromFile( (*it) + filename ) )
		{
			images_[filename] = image;
			std::cout << "DEBUG_MESSAGE: " << filename << " cargando imagen.\n";
			return images_[filename];
		}

	}

	std::cout << "GAME_ERROR: No se encontro la imagen. Se cargo una imagen vacia como reemplazo.\n";
	images_[filename] = image;
	return images_[filename];
}

void imageManager::deleteImage( const sf::Texture& image ) {
	for( std::map<std::string, sf::Texture>::const_iterator it = images_.begin();
		 it != images_.end(); 
		 ++it) {
		if( &image == &it->second ) {
			images_.erase( it );
                        return;
		}
	}
}

void imageManager::deleteImage( const std::string& filename ) {
	std::map<std::string, sf::Texture>::const_iterator it = images_.find( filename );
	if( it != images_.end() )
		images_.erase( it );
}

void imageManager::addResourceDirectory( const std::string& directory ) {
	//  Se chequea si la ruta existe
	for( std::vector<std::string>::const_iterator it  = resource_directories_.begin();
		 it != resource_directories_.end();
		++it ){
		// La ruta existe. Entonces no es necesario agregarla.
		if( directory == (*it) )
			return;
	}

	// Agregar la nueva ruta
	resource_directories_.push_back( directory );
}

void imageManager::removeResourceDirectory( const std::string& directory ) {
	for( std::vector<std::string>::iterator it  = resource_directories_.begin();
		 it != resource_directories_.end(); ) {
		// La ruta existe. Entonces no es necesario agregarla.
		if( directory == (*it) )
			it = resource_directories_.erase( it );
		else
			++it;
	}
}