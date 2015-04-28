#ifndef _BLOQUE_H_
#define _BLOQUE_H_

#include <SFML\Graphics.hpp>
#include <iostream>

class Bloque {
private:
	int			valor;
	sf::Sprite	sprite;
	sf::Text	text;

public:
	Bloque();
	~Bloque();

	int			GetValor() { return valor; }
	sf::Sprite	GetSprite() { return sprite; }
	sf::Text	GetText() { return text; }
	void		SetValor( int n ) { valor = n; }
	void		SetTexto( sf::Text tx ) { text = tx; }
	void		SetSprite( sf::Sprite sp ) { sprite = sp; }
	void		CambiarColor() { text.setColor( sf::Color::Green ); }
};

#endif