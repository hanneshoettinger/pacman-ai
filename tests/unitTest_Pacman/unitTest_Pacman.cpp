// unitTest_Pacman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"

// Include the header files for the Unit Test
#include "Pac.h"
#include "Ghosts.h"
#include "AI.h"

// test the AI logic of the ghosts with specific examples

TEST(TestAI, ShadowLogic)
{
	Ghosts shadowtest;
	Pac pactest;
	pactest.setpos(10,1);
	shadow_logic(&shadowtest, &pactest);
	EXPECT_EQ(shadowtest.targetx, pactest.getposx());
}

TEST(TestAI, SpeedyLogic)
{
	Ghosts speedytest;
	Pac pactest;
	pactest.setpos(10, 1);
	pactest.setdir(1, 0);
	speedy_logic(&speedytest, &pactest);
	EXPECT_EQ(speedytest.targetx, pactest.getposx() + 4 * pactest.getdirx());
	EXPECT_EQ(speedytest.targety, pactest.getposy() + 4 * pactest.getdiry());
}

TEST(TestAI, BashfulLogic)
{
	Ghosts bashfultest;
	Ghosts shadowtest;
	Pac pactest;
	pactest.setpos(8, 10);
	pactest.setdir(1, 0);

	shadowtest.setpos(10, 1);

	bashful_logic(&bashfultest, &shadowtest, &pactest);

	// actually checking y target, x stays at 10 since pac is heading to the same x as shadow
	// y -> 2* pacpos - shadowpos
	EXPECT_EQ(bashfultest.targetx, 10);
	EXPECT_EQ(bashfultest.targety, 19);
}

TEST(TestAI, PokeyLogic)
{
	Ghosts pokeytest;
	Pac pactest;
	pactest.setpos(10, 1);
	pactest.setdir(1, 0);
	// set pokey close to pacman -> go home
	pokeytest.setpos(8, 1);
	pokey_logic(&pokeytest, &pactest);
	EXPECT_EQ(pokeytest.targetx, 1);
	EXPECT_EQ(pokeytest.targety, 29);
	// set pokey far from pacman -> go to pac pos
	pokeytest.setpos(20, 1);
	pokey_logic(&pokeytest, &pactest);
	EXPECT_EQ(pokeytest.targetx, pactest.getposx());
	EXPECT_EQ(pokeytest.targety, pactest.getposy());
}
