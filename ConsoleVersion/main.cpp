#include "ExpenseTrackerLib\ExpenseTracker.h"

int main() {
    setlocale(LC_ALL, "");
    ExpenseTracker tracker;
    tracker.loadCategoriesFromFile();
    int choice;
    do{
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Добавить новую категорию расходов" << std::endl;
        std::cout << "2. Добавить новую категорию доходов" << std::endl;
        std::cout << "3. Вывести список категорий расходов" << std::endl;
        std::cout << "4. Вывести список категорий доходов" << std::endl;
        std::cout << "5. Сохранить категории в файл" << std::endl;
        std::cout << "6. Изменить сумму затрат для категории расходов" << std::endl;
        std::cout << "7. Изменить сумму затрат для категории доходов" << std::endl;
        std::cout << "8. Удалить категорию расходов" << std::endl;
        std::cout << "9. Удалить категорию доходов" << std::endl;
        std::cout << "10. Выход" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            std::string categoryName; double amount;
            std::cout << "Введите название новой категории расходов: ";
            std::cin >> categoryName;
            std::cout << "Введите сумму затрат для этой категории: ";
            std::cin >> amount;
            tracker.addExpenseCategory(categoryName, amount);
        }
        else if (choice == 2) {
            std::string categoryName; double amount;
            std::cout << "Введите название новой категории доходов: ";
            std::cin >> categoryName;
            std::cout << "Введите сумму доходов для этой категории: ";
            std::cin >> amount;
            tracker.addIncomeCategory(categoryName, amount);
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
            std::string categoryName;
            double amount;
            std::cout << "Введите название категории, для которой хотите изменить сумму затрат: ";
            std::cin >> categoryName;
            std::cout << "Введите новую сумму затрат: ";
            std::cin >> amount;
            tracker.updateExpenseCategoryAmount(categoryName, amount);
        }
        else if (choice == 7) {
            std::string categoryName;
            double amount;
            std::cout << "Введите название категории, для которой хотите изменить сумму затрат: ";
            std::cin >> categoryName;
            std::cout << "Введите новую сумму затрат: ";
            std::cin >> amount;
            tracker.updateIncomeCategoryAmount(categoryName, amount);
        }
        else if (choice == 8) {
            std::string categoryName;
            std::cout << "Введите название категории, которую хотите удалить: ";
            std::cin >> categoryName;
            tracker.dellExpenseEntry(categoryName);
        }
        else if (choice == 9) {
            std::string categoryName;
            std::cout << "Введите название категории, которую хотите удалить: ";
            std::cin >> categoryName;
            tracker.dellIncomeEntry(categoryName);
        }
        else {
            std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
        }
    } while (choice != 10);

    return 0;
}