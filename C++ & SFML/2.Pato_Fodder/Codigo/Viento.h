#include <SFML\System\Randomizer.hpp> //Para usar sf::Randomizer

class Viento
{
private:
	int dirViento, fuerzaViento;
	float timerViento, cambiaViento;

public:
	Viento();
	~Viento();

	void Update(float _ft);
	inline int getVelocidad() { return (dirViento * fuerzaViento); };
};