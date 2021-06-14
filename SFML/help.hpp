#ifndef NVX_SFML_HELP_HPP_72189
#define NVX_SFML_HELP_HPP_72189

#include <string>

#include <nvx/point.hpp>

#include <SFML/Graphics.hpp>





namespace nvx
{





sf::Color tocolor(std::string const &s);

inline void setCenteredPosition(sf::Text &text, PointF const &p)
{
	auto bounds = text.getGlobalBounds();
	text.setOrigin(
		0.50 * bounds.width,
		0.65 * bounds.height
	);
	text.setPosition( { p.x, p.y } );
	return;
}

inline void setCenteredPosition(sf::Text &text, float x, float y)
{
	return setCenteredPosition(text, { x, y });
}





}





#endif // NVX_SFML_HELP_HPP_72189
