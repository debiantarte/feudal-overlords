#include "pch.h"
#include "../FeudalOverlordsLibrary/AI.h"


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
