#include "Reaction.h" // Include the code that we are testing
#include <gtest/gtest.h> // Include the google test framework

class ReactionTest: public ::testing::Test {
protected:
	Reaction myReaction;
	Species calcium;
	Species carbon;
	Species oxygen;
	Species calcium_carbonate;
	ReactionTest():
		myReaction(5.0), 
		calcium("Ca"), 
		carbon("C"), 
		oxygen("O"), 
		calcium_carbonate("CaCO3")
	{
		calcium.SetConcentration(2.0);
		carbon.SetConcentration(3.0);
		oxygen.SetConcentration(5.0);
		calcium_carbonate.SetConcentration(7.0);
	};
};

// Test that the system has a name as expected.
TEST_F(ReactionTest, ReactionHasRate) { // First argument is test group, second is test name
  EXPECT_EQ(5.0, myReaction.GetRate()); // Assert that the name should be as expected
}

TEST_F(ReactionTest, ReactionCanHaveReactant) {
	myReaction.AddReactant(calcium);
	EXPECT_EQ(myReaction.GetReactants()[0]->GetName(),"Ca");
	EXPECT_EQ(myReaction.GetReactants()[0], &calcium);
}

TEST_F(ReactionTest, ReactionCanHaveReactants) {
	myReaction.AddReactant(calcium);
	myReaction.AddReactant(carbon);
	myReaction.AddReactant(oxygen);
	EXPECT_EQ(myReaction.GetReactants()[0]->GetName(),"Ca");
	EXPECT_EQ(myReaction.GetReactants()[0], &calcium);
	EXPECT_EQ(myReaction.GetReactants()[1], &carbon);
	EXPECT_EQ(myReaction.GetReactants()[2], &oxygen);
	EXPECT_EQ(myReaction.GetReactants().size(),3);
}

TEST_F(ReactionTest, ReactionCanHaveProduct) {
	myReaction.AddProduct(calcium_carbonate);
	EXPECT_EQ(myReaction.GetProducts()[0]->GetName(), "CaCO3");
	EXPECT_EQ(myReaction.GetProducts()[0], &calcium_carbonate);
}

TEST_F(ReactionTest, ReactionCanCalculateFlux) {
	myReaction.AddReactant(calcium);
	myReaction.AddReactant(carbon);
	myReaction.AddReactant(oxygen);
	myReaction.AddProduct(calcium_carbonate);

	EXPECT_EQ(5.0*2.0*3.0*5.0, myReaction.GetFlux());
}

TEST_F(ReactionTest, ReactionCanContributeToRatesOfChange) {
	myReaction.AddReactant(calcium);
	myReaction.AddReactant(carbon);
	myReaction.AddReactant(oxygen);
	myReaction.AddProduct(calcium_carbonate);

	myReaction.ContributeToRatesOfChange();

	EXPECT_EQ(-1.0*5.0*2.0*3.0*5.0, calcium.GetRateOfChange());
	EXPECT_EQ(-1.0*5.0*2.0*3.0*5.0, carbon.GetRateOfChange());
	EXPECT_EQ(-1.0*5.0*2.0*3.0*5.0, oxygen.GetRateOfChange());
	EXPECT_EQ(5.0*2.0*3.0*5.0, calcium_carbonate.GetRateOfChange());
}

int main(int argc, char **argv) { // A main function scaffold to call the tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}