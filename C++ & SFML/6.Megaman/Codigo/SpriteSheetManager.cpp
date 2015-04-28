#include "SpriteSheetManager.h"

void SpriteSheetManager::Load(std::string filename, unsigned nCols, unsigned nRows){
	// cargamos 
	const sf::Texture &sheet = TextureManager::GetInstance().GetTexture(filename);
	// segun la cantidad de filas/columnas calculamos el tamanio
	// de las subimagenes
	unsigned subimgw, subimgh;
	subimgw=sheet.getSize().x/nCols;
	subimgh=sheet.getSize().y/nRows;
	
	unsigned i, j;
	// r contendra la region de la imagen que nos interesa
	sf::IntRect r;
	
	// descomentar la linea siguiente si no quieren interpolacion
	//temp.SetSmooth(false);
	
	r.width = subimgw;
	r.height = subimgh;

	for(i=0; i<nRows; i++){
		for(j=0; j<nCols; j++){
			// cargamos r con los datos del rectangulo
			r.left=subimgw*j;
			r.top=subimgh*i;
			// insertarmos r en el vector			
			rects.push_back(r);
		}
	}
}

sf::IntRect &SpriteSheetManager::GetRect(unsigned i){
	return rects[i];
}

/*sf::IntRect &SpriteSheetManager::operator[](unsigned i){
	return rects[i];
	//return frames[i].rect;
}*/

unsigned SpriteSheetManager::Size(){
	return rects.size();
}

void SpriteSheetManager::pushRect(sf::IntRect r)
{
	rects.push_back(r);
}

//Para uso con clase FRAME y carga desde un archivo .json
void SpriteSheetManager::pushFrame( Frame frame )
{
	frames.push_back( frame );
}

Frame &SpriteSheetManager::getFrame( unsigned i )
{
	return frames[i];
}

void SpriteSheetManager::loadFromJson( std::string filename )
{
	Jzon::Object rootNode;
	Jzon::FileReader::ReadFile(filename, rootNode);
	const Jzon::Array &stuff = rootNode.Get("frames").AsArray();
	for (Jzon::Array::const_iterator it = stuff.begin(); it != stuff.end(); ++it)
	{
		Jzon::Object obj = (*it).AsObject();
		Jzon::Object frame = obj.Get("frame").AsObject();
		sf::IntRect r(
			frame.Get("x").ToInt(),
			frame.Get("y").ToInt(),
			frame.Get("w").ToInt(),
			frame.Get("h").ToInt()
			);
		Jzon::Object offset = obj.Get("offset").AsObject();
		sf::Vector2f off(offset.Get("x").ToInt(), offset.Get("y").ToInt());
		Frame f( r, off );
		frames.push_back( f );
	}
}

Frame &SpriteSheetManager::operator[](unsigned i)
{
	return frames[i];
}