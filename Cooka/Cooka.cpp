#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "Recipe.h"
using namespace std;

void ReadFile(vector<Recipe>& recipes) {

    ifstream inFile("Test_recipes.csv"); // creates stream to read from file

    if (!inFile.is_open()) { // if file does not open
        cout << "RAW_recipes.csv did not open." << endl;
    }
    else { // if file does open
        string tempString;
        getline(inFile, tempString); // reads first line

        // variables for recipe data
        string name;
        int minutes;
        int numSteps;
        string steps;
        string ingredient;
        int numIngredients;
        string temp;
        string temp2;

        while (getline(inFile, tempString)) {
            istringstream stream(tempString); // creates stream from line

            vector<string> ingredients;

            // store data into variables
            getline(stream, name, ',');
            getline(stream, temp, ',');
            minutes = stoi(temp);
            getline(stream, temp, ',');
            numSteps = stoi(temp);
            getline(stream, steps, ']');
            getline(stream, temp, ',');
            getline(stream, temp, ',');
            numIngredients = stoi(temp);
            getline(stream, temp, '\'');
            for (int i = 0; i < numIngredients; i++) {
                getline(stream, ingredient, '\'');
                /*if(ingredients.find(ingredient) == ingredients.end()) {
                  ingredients[ingredient] = i;
                }*/
                ingredients.push_back(ingredient);
                getline(stream, temp, '\'');
            }
            Recipe r(name, minutes, numSteps, steps, numIngredients, ingredients);
            recipes.push_back(r);
        }
    }
}

void CheckIngredient(string ingredient, vector<Recipe>& recipes) {
    for (int i = 0; i < recipes.size(); i++) {
        vector<string> rIngredients = recipes.at(i).GetIngredients();
        for (int j = 0; j < rIngredients.size(); j++) {
            if (rIngredients.at(j).find(ingredient) != string::npos) {
                recipes.at(i).IncrementCount();
                int recipeCount = recipes.at(i).GetCount();
            }
        }
    }
}

int main()
{
    vector<Recipe> recipes;
    ReadFile(recipes);

    // ask how many ingredients will be entered
    // for each ingredient entered, iterate over every recipe to check if the recipe uses the ingredient
    // if the recipe uses the ingredient, the ingredient count is incremented

    // Menu
    int userInput = 0;
    cout << "Welcome to COOKA!" << endl;
    while (userInput != 2) {
        cout << "\n1. LOOKA for a recipe" << endl;
        cout << "2. Exit" << endl;
        cin >> userInput;
        if (userInput == 1) {
            string ingredient;
            int numIngredients = 0;
            cout << "How many ingredients are you entering? ";
            cin >> numIngredients;
            for (int i = 0; i < numIngredients; i++) {
                cout << "Ingredient " << i + 1 << ": ";
                cin >> ingredient;
                CheckIngredient(ingredient, recipes);
            }
            cout << recipes[0].GetName() << ": " << recipes[0].GetCount() << endl;
        }
    }
}