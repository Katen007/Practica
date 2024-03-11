#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Category {
public:
    std::string name;
    double totalAmount;
    std::vector<std::string> entries;

    Category(const std::string& categoryName, double amount) : name(categoryName), totalAmount(amount) {}

    void addEntry(const std::string& entry, double amount) {
        entries.push_back(entry);
        totalAmount += amount;
    }
};

class ExpenseTracker {
private:
    std::vector<Category> expenseCategories;
    std::vector<Category> incomeCategories;

public:
    

    void loadCategoriesFromFile() {
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

      
    

    void saveCategoriesToFile() {
        std::ofstream file("categories.txt");

        for (const auto& category : expenseCategories) {
            file << category.name << " " << category.totalAmount << std::endl;

            for (const auto& entry : category.entries) {
                file << entry << std::endl;
            }
        }

        file.close();
    }

    void addExpenseCategory(const std::string& categoryName, double amount) {
        expenseCategories.push_back(Category(categoryName, amount));
    }

    void addIncomeCategory(const std::string& categoryName) {
        incomeCategories.push_back(Category(categoryName, 0.0));
    }

    void addExpenseEntry(int categoryIndex, const std::string& entry, double amount) {
        if (categoryIndex >= 0 && categoryIndex < expenseCategories.size()) {
            expenseCategories[categoryIndex].addEntry(entry, amount);
        }
    }

    void addIncomeEntry(int categoryIndex, const std::string& entry, double amount) {
        if (categoryIndex >= 0 && categoryIndex < incomeCategories.size()) {
            incomeCategories[categoryIndex].addEntry(entry, amount);
        }
    }

    void printExpenseCategories() {
        for (int i = 0; i < expenseCategories.size(); i++) {
            std::cout << i << ". " << expenseCategories[i].name << " - " << expenseCategories[i].totalAmount << std::endl;
        }
    }

    void printIncomeCategories() {
        for (int i = 0; i < incomeCategories.size(); i++) {
            std::cout << i << ". " << incomeCategories[i].name << std::endl;
        }
    }

    void updateExpenseCategoryAmount(int categoryIndex, double amount) {
        if (categoryIndex >= 0 && categoryIndex < expenseCategories.size()) {
            expenseCategories[categoryIndex].totalAmount = amount;
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    ExpenseTracker tracker;
    
    int choice;
    std::cout << "Выберите действие:" << std::endl;
    std::cout << "1. Добавить новую категорию расходов" << std::endl;
    std::cout << "2. Добавить новую категорию доходов" << std::endl;
    std::cout << "3. Вывести список категорий расходов" << std::endl;
    std::cout << "4. Вывести список категорий доходов" << std::endl;
    std::cout << "5. Сохранить категории в файл" << std::endl;
    std::cout << "6. Изменить сумму затрат для категории" << std::endl;
    std::cout << "7. Выход" << std::endl;
    std::cin >> choice;
    tracker.loadCategoriesFromFile();
    while (choice != 7) {
        if (choice == 1) {
            std::string categoryName; double amount;
            std::cout << "Введите название новой категории расходов: ";
            std::cin >> categoryName;
            std::cout << "Введите сумму затрат для этой категории: ";
            std::cin >> amount;
            tracker.addExpenseCategory(categoryName, amount);
        }
        else if (choice == 2) {
            std::string categoryName;
            std::cout << "Введите название новой категории доходов: ";
            std::cin >> categoryName;
            tracker.addIncomeCategory(categoryName);
        }
        else if (choice == 3) {
            std::cout << "Категории расходов:" << std::endl;
            tracker.printExpenseCategories();
        }
        else if (choice == 4) {
            std::cout << "Категории доходов:" << std::endl;
            tracker.printIncomeCategories();
        }
        else if (choice == 5) {
            tracker.saveCategoriesToFile();
            std::cout << "Категории сохранены в файл." << std::endl;
        }
        else if (choice == 6) {
            int categoryIndex;
            double amount;
            std::cout << "Введите индекс категории, для которой хотите изменить сумму затрат: ";
            std::cin >> categoryIndex;
            std::cout << "Введите новую сумму затрат: ";
            std::cin >> amount;
            tracker.updateExpenseCategoryAmount(categoryIndex, amount);
        }
        else {
            std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Добавить новую категорию расходов" << std::endl;
        std::cout << "2. Добавить новую категорию доходов" << std::endl;
        std::cout << "3. Вывести список категорий расходов" << std::endl;
        std::cout << "4. Вывести список категорий доходов" << std::endl;
        std::cout << "5. Сохранить категории в файл" << std::endl;
        std::cout << "6. Изменить сумму затрат для категории" << std::endl;
        std::cout << "7. Выход" << std::endl;
        std::cin >> choice;
    }

    return 0;
}