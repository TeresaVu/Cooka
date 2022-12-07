#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class Recipe
{
    string name;
    int minutes;
    int numSteps;
    string steps;
    vector<string> ingredients;
    int numIngredients;
    int count;

public:
    Recipe();
    Recipe(string name, int minutes, int numSteps, string steps, int numIngredients, vector<string>& ingredients);
    void PrintIngredients();
    string GetName();
    int GetCount();
    void SetCount(int count);
    vector<string> GetIngredients();
    void PrintInfo();
};



