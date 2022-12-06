#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Recipe.h"
using namespace std;

void ReadFile(vector<Recipe>& recipes) {

    ifstream inFile("RAW_recipes.csv"); // creates stream to read from file

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
            try {
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
            catch(exception& e) {

            }
        }
    }
}

void CheckIngredient(string ingredient, vector<Recipe>& recipes) {
    for (int i = 0; i < recipes.size(); i++) {
        vector<string> rIngredients = recipes.at(i).GetIngredients();
        for (int j = 0; j < rIngredients.size(); j++) {
            if (rIngredients.at(j).find(ingredient) != string::npos) {
                recipes.at(i).SetCount(recipes.at(i).GetCount() + 1);
            }
        }
    }
}

void ResetCount(vector<Recipe>& recipes) {
    for (int i = 0; i < recipes.size(); i++) {
        recipes[i].SetCount(0);
    }
}

int Partition(vector<Recipe>& recipes, int low, int high) {
    int pivot = recipes[high].GetCount();
    int up = low;
    int down = high;
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (recipes[up].GetCount() > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (recipes[down].GetCount() < pivot)
                break;
            down--;
        }
        if (up < down) {
            Recipe temp = recipes[up];
            recipes[up] = recipes[down];
            recipes[down] = temp;
        }
        Recipe temp = recipes[low];
        recipes[low] = recipes[down];
        recipes[down] = temp;
        return down;
    }
}

void QuickSort(vector<Recipe>& recipes, int low, int high) {
    if (low < high) {
        int pi = Partition(recipes, low, high);
        QuickSort(recipes, low, pi - 1);
        QuickSort(recipes, pi + 1, high);
    }
    /*int n = recipes.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Recipe temp = recipes[i];
            int j;
            for (j = i; j >= gap && recipes[j - gap].GetCount() < temp.GetCount(); j-= gap) {
                recipes[j] = recipes[j - gap];
            }
            recipes[j] = temp;
        }
    }*/
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
            cout << "\nHow many ingredients are you entering? ";
            cin >> numIngredients;
            for (int i = 0; i < numIngredients; i++) {
                cout << "Ingredient " << i+1 << ": ";
                cin >> ingredient;
                CheckIngredient(ingredient, recipes);
            }
            /*for (int i = 0; i < recipes.size(); i++) {
                cout << recipes[i].GetName() << ": " << recipes[i].GetCount() << endl;
            }*/
            int sort = 0;
            cout << "\n1. Shell Sort" << endl;
            cout << "2. Merge Sort" << endl;
            cin >> sort;
            if (sort == 1) {
                //vector<int> test = {4, 6, 7, 5, 8, 9};
                QuickSort(recipes, 0, recipes.size() - 1);
                for (int i = 0; i < 100; i++) {
                    cout << recipes[i].GetName() << ": " << recipes[i].GetCount() << endl;
                }
                /*for (int i = 0; i < test.size(); i++) {
                    cout << test[i] << endl;
                }*/
            }
            ResetCount(recipes);
        }
    }
}