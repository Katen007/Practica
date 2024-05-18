#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Category {
public:
    std::string name;
    double totalAmount;
    std::vector<std::string> entries;

    Category(const std::string& categoryName, double amount);

    void addEntry(const std::string& entry, double amount);
};

class ExpenseTracker {
private:
    std::vector<Category> expenseCategories;
    std::vector<Category> incomeCategories;

public:
    void loadCategoriesFromFile();
    void saveCategoriesToFile();
    void addExpenseCategory(const std::string& categoryName, double amount);
    void addIncomeCategory(const std::string& categoryName, double amount);
    void addExpenseEntry(int categoryIndex, const std::string& entry, double amount);
    void addIncomeEntry(int categoryIndex, const std::string& entry, double amount);
    void dellExpenseEntry(const std::string& entry);
    void dellIncomeEntry(const std::string& entry);
    int findExpenseCategories(const std::string& entry);
    int findIncomeCategories(const std::string& entry);
    void printExpenseCategories();
    void printIncomeCategories();
    void updateExpenseCategoryAmount(const std::string& entry, double amount);
    void updateIncomeCategoryAmount(const std::string& entry, double amount);
};