#pragma once

void CreateNewRecipe(std::string& recipeName, int& numOfIngredients, int& numOfSteps, RecipeManager& currentRecipe);

void AddItemToInventory(int& numOfItems, std::string& item, double& amount, double& cost, InventoryManager& inventory);

void Prompts(int& selInput);
