#include "TextureManager.h"
using namespace std;

// se debe inicializar la instancia �nica est�tica
TextureManager *TextureManager::instance = NULL;

// constructor
TextureManager::TextureManager(){
	smooth = false;
}

// en caso de no encontrar una determinada textura en el mapa, esta funci�n
// la carga desde el disco. Es llamada desde GetInstance()
const sf::Texture &TextureManager::LoadTexture(const std::string &name){
	// crea un objeto sf::Texture y lo agrega al mapa
	sf::Texture i;
	pair<map<string, sf::Texture>::iterator, bool> p=textures.insert(pair<string, sf::Texture>(name, i));
	// una vez que dicho objeto est� cargado, se llama a LoadFromFile() para cargar la textura en dicho
	// objeto. Esto se realiza despu�s de cargar al objeto sf::Texture en el mapa y no antes por cuestiones
	// de eficiencia: luego de llamar a LoadFromFile() el objeto ser� m�s pesado porque contendr� la textura,
	// por esta raz�n, requerir� m�s tiempo para ser copiado, y la inserci�n en el mapa requiere hacer una copia.
	sf::Texture &img = p.first->second;
	if(!img.loadFromFile(name)){
		cout<<"ERROR en carga de imagen " << name <<endl;
	} else
		cout<<"Cargada la imagen "<< name << endl;
	// finalmente se habilita el filtrado en la nueva textura cargada segun corresponda
	img.setSmooth(smooth);
	return img;
}

// devuelve la instancia �nica del manejador
TextureManager &TextureManager::GetInstance(){
	if (instance == NULL) instance = new TextureManager();
	return *instance;
}

// busca una textura a partir de su nombre de archivo
// si no la encuentra en el mapa, intenta cargarla desde el dico
const sf::Texture &TextureManager::GetTexture(const string &name){
	map<string, sf::Texture>::iterator p=textures.find(name);
	if(p != textures.end()){
		return p->second;
	}else{
		return LoadTexture(name);
	}
	
}

// cumple la misma funci�n que GetTexture()
const sf::Texture &TextureManager::operator[](const string &name){
	return GetTexture(name);
}

// habilita/desabilita el filtrado para las texturas
void TextureManager::SmoothTextures(bool smooth){
	this->smooth = smooth;
	// adem�s de cambiar la flag, es necesario cambiar
	// las texturas que ya fueron cargadas
	map<string, sf::Texture>::iterator p=textures.begin();
	while(p != textures.end()){
		p->second.setSmooth(smooth);
		p++;
	}
	
}