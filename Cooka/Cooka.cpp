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

// Merge two subarrays from arr
void merge(vector<Recipe>& recipes, int left, int mid, int right)
{
    // Create X -> recipes[left..mid] & Y -> recipes[mid+1..right]
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Recipe> X(n1), Y(n2);
    for (int i = 0; i < n1; i++)
        X[i] = recipes[left + i];
    for (int j = 0; j < n2; j++)
        Y[j] = recipes[mid + 1 + j];
    // Merge the arrays X and Y into recipes vector
    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (X[i].GetCount() >= Y[j].GetCount())
        {
            recipes[k] = X[i];
            i++;
        }
        else
        {
            recipes[k] = Y[j];
            j++;
        }
        k++;
    }
    // When we run out of elements in either X or Y append the remaining elements
    while (i < n1)
    {
        recipes[k] = X[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        recipes[k] = Y[j];
        j++;
        k++;
    }
}

// mergeSort and merge code from lecture module 6 - sorting
void mergeSort(vector<Recipe>& recipes, int left, int right)
{
    if (left < right)
    {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;
        mergeSort(recipes, left, mid);
        mergeSort(recipes, mid + 1, right);
        // Merge the sorted subarrays
        merge(recipes, left, mid, right);
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
        }
        cout << recipes.size() << " results" << endl;
        cout << "Select sorting algorithm: " << endl;
        cout << "1. Shell Sort" << endl;
        cout << "2. Merge Sort" << endl;
        cin >> userInput;
        if (userInput == 2) {
            mergeSort(recipes, 0, recipes.size() - 1);
            for (int i = 0; i < recipes.size(); i++) {
                cout << recipes.at(i).GetName() << ": " << recipes.at(i).GetCount() << endl;
            }
        }
    }
}