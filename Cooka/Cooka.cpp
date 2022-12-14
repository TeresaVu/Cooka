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

// check is each recipe contains the specified ingredient and increment its count if so
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

int Partition(vector<Recipe>& recipes, int low, int high) {
    int pivot = recipes[low].GetCount();
    int up = low;
    int down = high;
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (recipes[up].GetCount() < pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (recipes[down].GetCount() > pivot)
                break;
            down--;
        }
        if (up < down) {
            swap(recipes[up], recipes[down]);
        }
        swap(recipes[low], recipes[down]);

        return down;
    }
}

void QuickSort(vector<Recipe>& recipes, int low, int high) {
    if (low < high) {
        int pi = Partition(recipes, low, high);
        QuickSort(recipes, low, pi - 1);
        QuickSort(recipes, pi + 1, high);
    }
}

// Merge two subarrays from arr
void merge(vector<Recipe>& recipes, int left, int mid, int right) {
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
void MergeSort(vector<Recipe>& recipes, int left, int right)
{
    if (left < right)
    {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;
        MergeSort(recipes, left, mid);
        MergeSort(recipes, mid + 1, right);
        // Merge the sorted subarrays
        merge(recipes, left, mid, right);
    }
}

// output the recipes in groups of 10 or display extended recipe information
void DisplayRecipes(vector<Recipe>& recipes) {
    int userInput = 2;
    int index = 0;
    for (int i = 0; i < 10; i++) {
        cout << index + 1 << ". " << recipes[index].GetName() << ": " << recipes[index].GetCount();
        if (recipes[index].GetCount() == 1) {
            cout << " match" << endl;
        }
        else {
            cout << " matches" << endl;
        }
        index++;
        if (index % 10 == 0) { ;
            cout << "---Showing " << index << " of " << recipes.size() << " recipes---\n\n" << endl;
            if (index == recipes.size()) {
                break;
            }
            cout << "1. Find recipe information" << endl;
            cout << "2. Load 10 more recipes" << endl;
            cout << "3. Exit" << endl;
            cout << "Selection: ";
            cin >> userInput;
            cout << endl;
        }
    }
    while (index < recipes.size()) {
        if (userInput == 1) {
            int userInput2 = 0;
            cout << "Enter recipe number: ";
            cin >> userInput2;
            recipes[userInput2 - 1].PrintInfo();
            cout << "1. Find recipe information" << endl;
            cout << "2. Load 10 more recipes" << endl;
            cout << "3. Exit" << endl;
            cout << "Selection: ";
            cin >> userInput;
            cout << endl;

        }
        else if (userInput == 2) {
            cout << index + 1 << ". " << recipes[index].GetName() << ": " << recipes[index].GetCount();
            if (recipes[index].GetCount() == 1) {
                cout << " match" << endl;
            }
            else {
                cout << " matches" << endl;
            }
            index++;
            if (index % 10 == 0) {
                cout << "---Showing " << index << " of " << recipes.size() << " recipes---\n\n" << endl;
                if (index == recipes.size()) {
                    cout << "1. Find recipe information" << endl;
                    cout << "2. Exit" << endl;
                    cout << "Selection: ";
                    cin >> userInput;
                    cout << endl;
                    if (userInput == 1) {
                        int userInput2;
                        cout << "Enter recipe number: ";
                        cin >> userInput2;
                        recipes[userInput2 - 1].PrintInfo();
                    }
                    break;
                }
                cout << "1. Find recipe information" << endl;
                cout << "2. Load 10 more recipes" << endl;
                cout << "3. Exit" << endl;
                cout << "Selection: ";
                cin >> userInput;
                cout << endl;
            }
        }
        else if (userInput == 3) {
            break;
        }
    }
}

int main()
{
    vector<Recipe> recipes;

    // ask how many ingredients will be entered
    // for each ingredient entered, iterate over every recipe to check if the recipe uses the ingredient
    // if the recipe uses the ingredient, the ingredient count is incremented

    // Menu
    int userInput = 0;
    cout << "Welcome to COOKA!" << endl;
    cout << "-----------------";
    cout << "\n1. LOOKA for a recipe" << endl;
    cout << "2. Exit" << endl;
    cout << "Selection: ";
    cin >> userInput;
    if (userInput == 1) {
        cout << "\nLoading recipes..." << endl;
        ReadFile(recipes);
        string ingredient;
        int numIngredients = 0;
        cout << "\nHow many ingredients are you entering? ";
        cin >> numIngredients;
        for (int i = 0; i < numIngredients; i++) {
            cout << "Ingredient " << i+1 << ": ";
            cin >> ingredient;
            CheckIngredient(ingredient, recipes);
        }
        int sort = 0;
        cout << "\nSort results by: ";
        cout << "\n1. Quick Sort" << endl;
        cout << "2. Merge Sort" << endl;
        cout << "Selection: ";
        cin >> sort;
        cout << endl;
        if (sort == 1) {
            for (int i = 0; i < recipes.size(); i++) {
                QuickSort(recipes, 0, recipes.size() - 1);
            }
            DisplayRecipes(recipes);
        }
        else if (sort == 2) {
            MergeSort(recipes, 0, recipes.size() - 1);
            DisplayRecipes(recipes);
        }
    }
}