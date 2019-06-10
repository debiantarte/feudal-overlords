#include "pch.h"
#include "../FeudalOverlordsLibrary/AI.h"
#include "../FeudalOverlordsLibrary/GameManager.h"

TEST(TestAI, TestRebel) {
	AI ai = AI();
	vector<int> psychology = ai.getPsychology();
	for (int trait : psychology)
	{
		EXPECT_GT(trait, 0);
		EXPECT_LT(trait, 100);
	}
	double approval = ai.approve();
	if (approval > 50)
	{
		EXPECT_FALSE(ai.rebel(approval));
	}
	else if (approval > 25 && ai.getGoal() == winWithOverlord)
	{
		EXPECT_FALSE(ai.rebel(approval));
	}
	else
	{
		EXPECT_TRUE(ai.rebel(approval));
	}
}

TEST(TestGameManager, TestTerritoryCount) {
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	GameManager gameManager(99, players, pair<int, int>(300, 200), 3);
	map<shared_ptr<Lord>, int> res_map = gameManager.territoryCount();
	EXPECT_EQ(res_map.size(), 100);
	for (auto count_pair : res_map)
	{
		EXPECT_EQ(count_pair.second, 1);
	}
}

TEST(TestGameManager, TestGameFinishedConquest)
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	GameManager gameManager(99, players, pair<int, int>(300, 200), 3);
	EXPECT_FALSE(gameManager.isGameFinished());
	for (auto& territory : gameManager.board.territories)
	{
		territory->setOwner(players[0]);
	}
	EXPECT_TRUE(gameManager.isGameFinished());
}

TEST(TestGameManager, TestGameFinishedTurns)
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "Elizabeth"));
	GameManager gameManager(99, players, pair<int, int>(300, 200), 3);
	EXPECT_FALSE(gameManager.isGameFinished());
	gameManager.setTurn(3);
	EXPECT_TRUE(gameManager.isGameFinished());
}

TEST(TestGameManager, TestWinner)
{
	vector<shared_ptr<Player>> players;
	players.push_back(make_shared<Player>((string) "xXXTesterXXx"));
	GameManager gameManager(99, players, pair<int, int>(300, 200), 3);
	EXPECT_EQ(gameManager.winner(), nullptr);
	for (int i=0; i<2; i++)
	{
		auto& territory = gameManager.board.territories[i];
		territory->setOwner(players[0]);
	}
	gameManager.setTurn(3);
	EXPECT_TRUE(gameManager.isGameFinished());
	EXPECT_EQ(gameManager.winner(), players[0]);

}
