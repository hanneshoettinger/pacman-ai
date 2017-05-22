#pragma once

#include <SFML/Graphics.hpp>

#ifndef SPRITES_H
#define SPRITES_H

class Sprites
{
public:

	void InitTextures();

	sf::Texture texture;
	sf::Sprite shadowsprite;
	sf::Sprite speedysprite;
	sf::Sprite bashfulsprite;
	sf::Sprite pokeysprite;
	sf::Sprite escapesprite;
	sf::Texture eyestext;
	sf::Sprite eyesup;
	sf::Sprite eyesright;
	sf::Sprite eyesdown;
	sf::Sprite eyesleft;
	sf::Texture pactext;
	sf::Sprite pacup;
	sf::Sprite pacright;
	sf::Sprite pacdown;
	sf::Sprite pacleft;
	sf::Texture bigdot;
	sf::Sprite big_dot;
	sf::Texture dot;
	sf::Sprite dot_1;
	sf::Texture bottomleft;
	sf::Sprite corner_bottom_left;
	sf::Texture bottomright;
	sf::Sprite corner_bottom_right;
	sf::Texture topleft;
	sf::Sprite corner_top_left;
	sf::Texture topright;
	sf::Sprite corner_top_right;
	sf::Texture door;
	sf::Sprite door_1;
	sf::Texture gateleft;
	sf::Sprite gate_left;
	sf::Texture gateright;
	sf::Sprite gate_right;
	sf::Texture outercornerbottomleft;
	sf::Sprite outercorner_bottom_left;
	sf::Texture outercornerbottomright;
	sf::Sprite outercorner_bottom_right;
	sf::Texture outercornernarrowbottomleft;
	sf::Sprite outercorner_narrow_bottom_left;
	sf::Texture outercornernarrowbottomright;
	sf::Sprite outercorner_narrow_bottom_right;
	sf::Texture outercornernarrowtopleft;
	sf::Sprite outercorner_narrow_top_left;
	sf::Texture outercornernarrowtopright;
	sf::Sprite outercorner_narrow_top_right;
	sf::Texture outercornertopleft;
	sf::Sprite outercorner_top_left;
	sf::Texture outercornertopright;
	sf::Sprite outercorner_top_right;
	sf::Texture outernosebottomleft;
	sf::Sprite outernose_bottom_left;
	sf::Texture outernosebottomright;
	sf::Sprite outernose_bottom_right;
	sf::Texture outernoseleftbottom;
	sf::Sprite outernose_left_bottom;
	sf::Texture outernoselefttop;
	sf::Sprite outernose_left_top;
	sf::Texture outernoserightbottom;
	sf::Sprite outernose_right_bottom;
	sf::Texture outernoserighttop;
	sf::Sprite outernose_right_top;
	sf::Texture outernosetopleft;
	sf::Sprite outernose_top_left;
	sf::Texture outernosetopright;
	sf::Sprite outernose_top_right;
	sf::Texture outerwallbottom;
	sf::Sprite outerwall_bottom;
	sf::Texture outerwallleft;
	sf::Sprite outerwall_left;
	sf::Texture outerwallright;
	sf::Sprite outerwall_right;
	sf::Texture outerwalltop;
	sf::Sprite outerwall_top;
	sf::Texture pacman;
	sf::Sprite pacman_1;
	sf::Texture wallbottom;
	sf::Sprite wall_bottom;
	sf::Texture wallleft;
	sf::Sprite wall_left;
	sf::Texture wallright;
	sf::Sprite wall_right;
	sf::Texture walltop;
	sf::Sprite wall_top;
};

#endif