#include "ExpenseTracker.h"

Category::Category(const std::string& categoryName, double amount) : name(categoryName), totalAmount(amount) {}

void Category::addEntry(const std::string& entry, double amount) {
    entries.push_back(entry);
    totalAmount += amount;
}

void ExpenseTracker::loadCategoriesFromFile() {
    std::ifstream file("categories.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::string categoryName;
        double amount = 0;
        size_t spaceIndex = line.find(' ');

        if (spaceIndex != std::string::npos) {
            categoryName = line.substr(0, spaceIndex);

            std::string amountString = line.substr(spaceIndex + 1);
            bool decimalPart = false;
            double decimalMultiplier = 0.1;

            for (char c : amountString) {
                if (c >= '0' && c <= '9') {
                    if (decimalPart) {
                        amount += (c - '0') * decimalMultiplier;
                        decimalMultiplier *= 0.1;
                    }
                    else {
                        amount = amount * 10 + (c - '0');
                    }
                }
                else if (c == '.') {
                    decimalPart = true;
                }
                else {
                    std::cout << "Ошибка при чтении строки: " << line << std::endl;
                    break;
                }
            }

            expenseCategories.push_back(Category(categoryName, amount));
        }
        else {
            std::cout << "Ошибка при чтении строки: " << line << std::endl;
        }
    }

    file.close();
}

void ExpenseTracker::saveCategoriesToFile() {
    std::ofstream file("categories.txt");

    for (const auto& category : expenseCategories) {
        file << category.name << " " << category.totalAmount << std::endl;

        for (const auto& entry : category.entries) {
            file << entry << std::endl;
        }
    }

    file.close();
}

int ExpenseTracker::findExpenseCategories(const std::string& entry) {
    for (int i = 0; i < expenseCategories.size(); i++) {
        if (expenseCategories[i].name == entry) {
            return i;
        }
        return -1;
    }
}

int ExpenseTracker::findIncomeCategories(const std::string& entry) {
    for (int i = 0; i < incomeCategories.size(); i++) {
        if (incomeCategories[i].name == entry) {
            return i;
        }
        return -1;
    }
}

void ExpenseTracker::dellIncomeEntry(const std::string& entry) {
    int index = findIncomeCategories(entry);
    if (index != -1) {
        incomeCategories.erase(incomeCategories.begin()+index);
    }
    else {
        std::cout << "Категория не найдена\n";
    }
}

void ExpenseTracker::dellExpenseEntry(const std::string& entry) {
    int index = findExpenseCategories(entry);
    if (index != -1) {
        expenseCategories.erase(expenseCategories.begin() + index);
    }
    else {
        std::cout << "Категория не найдена\n";
    }
}

void ExpenseTracker::addExpenseCategory(const std::string& categoryName, double amount) {
    expenseCategories.push_back(Category(categoryName, amount));
}

void ExpenseTracker::addIncomeCategory(const std::string& categoryName, double amount) {
    incomeCategories.push_back(Category(categoryName, amount));
}

void ExpenseTracker::addExpenseEntry(int categoryIndex, const std::string& entry, double amount) {
    if (categoryIndex >= 0 && categoryIndex < expenseCategories.size()) {
        expenseCategories[categoryIndex].addEntry(entry, amount);
    }
}

void ExpenseTracker::addIncomeEntry(int categoryIndex, const std::string& entry, double amount) {
    if (categoryIndex >= 0 && categoryIndex < incomeCategories.size()) {
        incomeCategories[categoryIndex].addEntry(entry, amount);
    }
}

void ExpenseTracker::printExpenseCategories() {
    for (int i = 0; i < expenseCategories.size(); i++) {
        std::cout << i << ". " << expenseCategories[i].name << " - " << expenseCategories[i].totalAmount << std::endl;
    }
}

void ExpenseTracker::printIncomeCategories() {
    for (int i = 0; i < incomeCategories.size(); i++) {
        std::cout << i << ". " << incomeCategories[i].name << " - " << incomeCategories[i].totalAmount << std::endl;
    }
}

void ExpenseTracker::updateExpenseCategoryAmount(const std::string& entry, double amount) {
    int categoryIndex = findExpenseCategories(entry);
    if (categoryIndex != -1) {
        if (categoryIndex >= 0 && categoryIndex < expenseCategories.size()) {
            expenseCategories[categoryIndex].totalAmount = amount;
        }
    }
    else {
        std::cout << "Категория не найдена\n";
    }
   
}

void ExpenseTracker::updateIncomeCategoryAmount(const std::string& entry, double amount) {
    int categoryIndex = findIncomeCategories(entry);
    if (categoryIndex != -1) {
        if (categoryIndex >= 0 && categoryIndex < incomeCategories.size()) {
            incomeCategories[categoryIndex].totalAmount = amount;
        }
    }
    else {
        std::cout << "Категория не найдена\n";
    }

}