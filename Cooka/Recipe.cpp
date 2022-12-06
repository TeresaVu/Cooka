#include "Recipe.h"

Recipe::Recipe() {
	name = "";
	minutes = 0;
	numSteps = 0;
	numIngredients = 0;
	count = 0;
};

Recipe::Recipe(string name, int minutes, int numSteps, string steps, int numIngredients, vector<string>& ingredients) {
	this->name = name;
	this->minutes = minutes;
	this->numSteps = numSteps;
	this->steps = steps;
	this->numIngredients = numIngredients;
	this->ingredients = ingredients;
	this->count = 0;
};

void Recipe::PrintIngredients() {
	// for (auto it = ingredients.begin(); it != ingredients.end(); it++) {
	//   cout << it->first << endl;
	// }
	for (int i = 0; i < ingredients.size(); i++) {
		cout << ingredients.at(i) << endl;
	}
};

string Recipe::GetName() {
	return name;
}

int Recipe::GetCount() {
	return count;
}

void Recipe::SetCount(int count) {
	this->count = count;
}

void Recipe::IncrementCount() {
	this->count++;
}

vector<string> Recipe::GetIngredients() {
	return ingredients;
}