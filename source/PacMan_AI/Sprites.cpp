#include "stdafx.h"
#include "Sprites.h"

// Initialize the Textures
void Sprites::InitTextures()
{
	if (!texture.loadFromFile("./pacman/gfx/sprites/monster_2.png"))
		std::cout << "Error";

	shadowsprite.setTexture(texture);
	shadowsprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	shadowsprite.scale(0.5f, 0.5f);  //set to 16x16

	speedysprite.setTexture(texture);
	speedysprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
	speedysprite.scale(0.5f, 0.5f);  //set to 16x16

	bashfulsprite.setTexture(texture);
	bashfulsprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
	bashfulsprite.scale(0.5f, 0.5f);  //set to 16x16

	pokeysprite.setTexture(texture);
	pokeysprite.setTextureRect(sf::IntRect(192, 0, 32, 32));
	pokeysprite.scale(0.5f, 0.5f);  //set to 16x16

	escapesprite.setTexture(texture);
	escapesprite.setTextureRect(sf::IntRect(512, 0, 32, 32));
	escapesprite.scale(0.5f, 0.5f);  //set to 16x16


	if (!eyestext.loadFromFile("./pacman/gfx/sprites/eyes.png"))
		std::cout << "Error";

	eyesup.setTexture(eyestext);
	eyesup.setTextureRect(sf::IntRect(0, 0, 32, 32));
	eyesup.scale(0.5f, 0.5f);  //set to 16x16

	eyesright.setTexture(eyestext);
	eyesright.setTextureRect(sf::IntRect(32, 0, 32, 32));
	eyesright.scale(0.5f, 0.5f);  //set to 16x16

	eyesdown.setTexture(eyestext);
	eyesdown.setTextureRect(sf::IntRect(64, 0, 32, 32));
	eyesdown.scale(0.5f, 0.5f);  //set to 16x16

	eyesleft.setTexture(eyestext);
	eyesleft.setTextureRect(sf::IntRect(96, 0, 32, 32));
	eyesleft.scale(0.5f, 0.5f);  //set to 16x16

	if (!pactext.loadFromFile("./pacman/gfx/sprites/pacman.png"))
		std::cout << "Error";
	pacup.setTexture(pactext);
	pacup.setTextureRect(sf::IntRect(32, 0, 32, 32));
	pacup.scale(0.5f, 0.5f);  //set to 16x16

	pacright.setTexture(pactext);
	pacright.setTextureRect(sf::IntRect(128, 0, 32, 32));
	pacright.scale(0.5f, 0.5f);  //set to 16x16

	pacdown.setTexture(pactext);
	pacdown.setTextureRect(sf::IntRect(224, 0, 32, 32));
	pacdown.scale(0.5f, 0.5f);  //set to 16x16

	pacleft.setTexture(pactext);
	pacleft.setTextureRect(sf::IntRect(320, 0, 32, 32));
	pacleft.scale(0.5f, 0.5f);  //set to 16x16

	if (!bigdot.loadFromFile("./pacman/gfx/tiles/big_dot.png"))
		std::cout << "Error";
	big_dot.setTexture(bigdot);
	big_dot.scale(0.16f, 0.16f);  //set to 16x16

	if (!dot.loadFromFile("./pacman/gfx/tiles/dot.png"))
		std::cout << "Error";
	dot_1.setTexture(dot);
	dot_1.scale(0.16f, 0.16f);  //set to 16x16

	if (!bottomleft.loadFromFile("./pacman/gfx/tiles/corner_bottom_left.png"))
		std::cout << "Error";
	corner_bottom_left.setTexture(bottomleft);
	corner_bottom_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!bottomright.loadFromFile("./pacman/gfx/tiles/corner_bottom_right.png"))
		std::cout << "Error";
	corner_bottom_right.setTexture(bottomright);
	corner_bottom_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!topleft.loadFromFile("./pacman/gfx/tiles/corner_top_left.png"))
		std::cout << "Error";
	corner_top_left.setTexture(topleft);
	corner_top_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!topright.loadFromFile("./pacman/gfx/tiles/corner_top_right.png"))
		std::cout << "Error";
	corner_top_right.setTexture(topright);
	corner_top_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!door.loadFromFile("./pacman/gfx/tiles/door.png"))
		std::cout << "Error";
	door_1.setTexture(door);
	door_1.scale(0.16f, 0.16f);  //set to 16x16

	if (!gateleft.loadFromFile("./pacman/gfx/tiles/gate_left.png"))
		std::cout << "Error";
	gate_left.setTexture(gateleft);
	gate_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!gateright.loadFromFile("./pacman/gfx/tiles/gate_right.png"))
		std::cout << "Error";
	gate_right.setTexture(gateright);
	gate_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornerbottomleft.loadFromFile("./pacman/gfx/tiles/outercorner_bottom_left.png"))
		std::cout << "Error";
	outercorner_bottom_left.setTexture(outercornerbottomleft);
	outercorner_bottom_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornerbottomright.loadFromFile("./pacman/gfx/tiles/outercorner_bottom_right.png"))
		std::cout << "Error";
	outercorner_bottom_right.setTexture(outercornerbottomright);
	outercorner_bottom_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornernarrowbottomleft.loadFromFile("./pacman/gfx/tiles/outercorner_narrow_bottom_left.png"))
		std::cout << "Error";
	outercorner_narrow_bottom_left.setTexture(outercornernarrowbottomleft);
	outercorner_narrow_bottom_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornernarrowbottomright.loadFromFile("./pacman/gfx/tiles/outercorner_narrow_bottom_right.png"))
		std::cout << "Error";
	outercorner_narrow_bottom_right.setTexture(outercornernarrowbottomright);
	outercorner_narrow_bottom_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornernarrowtopleft.loadFromFile("./pacman/gfx/tiles/outercorner_narrow_top_left.png"))
		std::cout << "Error";
	outercorner_narrow_top_left.setTexture(outercornernarrowtopleft);
	outercorner_narrow_top_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornernarrowtopright.loadFromFile("./pacman/gfx/tiles/outercorner_narrow_top_right.png"))
		std::cout << "Error";
	outercorner_narrow_top_right.setTexture(outercornernarrowtopright);
	outercorner_narrow_top_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornertopleft.loadFromFile("./pacman/gfx/tiles/outercorner_top_left.png"))
		std::cout << "Error";
	outercorner_top_left.setTexture(outercornertopleft);
	outercorner_top_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outercornertopright.loadFromFile("./pacman/gfx/tiles/outercorner_top_right.png"))
		std::cout << "Error";
	outercorner_top_right.setTexture(outercornertopright);
	outercorner_top_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernosebottomleft.loadFromFile("./pacman/gfx/tiles/outernose_bottom_left.png"))
		std::cout << "Error";
	outernose_bottom_left.setTexture(outernosebottomleft);
	outernose_bottom_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernosebottomright.loadFromFile("./pacman/gfx/tiles/outernose_bottom_right.png"))
		std::cout << "Error";
	outernose_bottom_right.setTexture(outernosebottomright);
	outernose_bottom_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernoseleftbottom.loadFromFile("./pacman/gfx/tiles/outernose_left_bottom.png"))
		std::cout << "Error";
	outernose_left_bottom.setTexture(outernoseleftbottom);
	outernose_left_bottom.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernoselefttop.loadFromFile("./pacman/gfx/tiles/outernose_left_top.png"))
		std::cout << "Error";
	outernose_left_top.setTexture(outernoselefttop);
	outernose_left_top.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernoserightbottom.loadFromFile("./pacman/gfx/tiles/outernose_right_bottom.png"))
		std::cout << "Error";
	outernose_right_bottom.setTexture(outernoserightbottom);
	outernose_right_bottom.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernoserighttop.loadFromFile("./pacman/gfx/tiles/outernose_right_top.png"))
		std::cout << "Error";
	outernose_right_top.setTexture(outernoserighttop);
	outernose_right_top.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernosetopleft.loadFromFile("./pacman/gfx/tiles/outernose_top_left.png"))
		std::cout << "Error";
	outernose_top_left.setTexture(outernosetopleft);
	outernose_top_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outernosetopright.loadFromFile("./pacman/gfx/tiles/outernose_top_right.png"))
		std::cout << "Error";
	outernose_top_right.setTexture(outernosetopright);
	outernose_top_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outerwallbottom.loadFromFile("./pacman/gfx/tiles/outerwall_bottom.png"))
		std::cout << "Error";
	outerwall_bottom.setTexture(outerwallbottom);
	outerwall_bottom.scale(0.16f, 0.16f);  //set to 16x16

	if (!outerwallleft.loadFromFile("./pacman/gfx/tiles/outerwall_left.png"))
		std::cout << "Error";
	outerwall_left.setTexture(outerwallleft);
	outerwall_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!outerwallright.loadFromFile("./pacman/gfx/tiles/outerwall_right.png"))
		std::cout << "Error";
	outerwall_right.setTexture(outerwallright);
	outerwall_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!outerwalltop.loadFromFile("./pacman/gfx/tiles/outerwall_top.png"))
		std::cout << "Error";
	outerwall_top.setTexture(outerwalltop);
	outerwall_top.scale(0.16f, 0.16f);  //set to 16x16

	if (!pacman.loadFromFile("./pacman/gfx/tiles/pacman.png"))
		std::cout << "Error";
	pacman_1.setTexture(pacman);
	pacman_1.scale(0.16f, 0.16f);  //set to 16x16

	if (!wallbottom.loadFromFile("./pacman/gfx/tiles/wall_bottom.png"))
		std::cout << "Error";
	wall_bottom.setTexture(wallbottom);
	wall_bottom.scale(0.16f, 0.16f);  //set to 16x16

	if (!wallleft.loadFromFile("./pacman/gfx/tiles/wall_left.png"))
		std::cout << "Error";
	wall_left.setTexture(wallleft);
	wall_left.scale(0.16f, 0.16f);  //set to 16x16

	if (!wallright.loadFromFile("./pacman/gfx/tiles/wall_right.png"))
		std::cout << "Error";
	wall_right.setTexture(wallright);
	wall_right.scale(0.16f, 0.16f);  //set to 16x16

	if (!walltop.loadFromFile("./pacman/gfx/tiles/wall_top.png"))
		std::cout << "Error";
	wall_top.setTexture(walltop);
	wall_top.scale(0.16f, 0.16f);  //set to 16x16
}
