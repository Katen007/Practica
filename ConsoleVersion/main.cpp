#include "ExpenseTrackerLib\ExpenseTracker.h"

int main() {
    setlocale(LC_ALL, "");
    ExpenseTracker tracker;
    tracker.loadCategoriesFromFile();
    int choice;
    do{
        std::cout << "�������� ��������:" << std::endl;
        std::cout << "1. �������� ����� ��������� ��������" << std::endl;
        std::cout << "2. �������� ����� ��������� �������" << std::endl;
        std::cout << "3. ������� ������ ��������� ��������" << std::endl;
        std::cout << "4. ������� ������ ��������� �������" << std::endl;
        std::cout << "5. ��������� ��������� � ����" << std::endl;
        std::cout << "6. �������� ����� ������ ��� ��������� ��������" << std::endl;
        std::cout << "7. �������� ����� ������ ��� ��������� �������" << std::endl;
        std::cout << "8. ������� ��������� ��������" << std::endl;
        std::cout << "9. ������� ��������� �������" << std::endl;
        std::cout << "10. �����" << std::endl;
        std::cin >> choice;

        if (choice == 1) {
            std::string categoryName; double amount;
            std::cout << "������� �������� ����� ��������� ��������: ";
            std::cin >> categoryName;
            std::cout << "������� ����� ������ ��� ���� ���������: ";
            std::cin >> amount;
            tracker.addExpenseCategory(categoryName, amount);
        }
        else if (choice == 2) {
            std::string categoryName; double amount;
            std::cout << "������� �������� ����� ��������� �������: ";
            std::cin >> categoryName;
            std::cout << "������� ����� ������� ��� ���� ���������: ";
            std::cin >> amount;
            tracker.addIncomeCategory(categoryName, amount);
        }
        else if (choice == 3) {
            std::cout << "��������� ��������:" << std::endl;
            tracker.printExpenseCategories();
        }
        else if (choice == 4) {
            std::cout << "��������� �������:" << std::endl;
            tracker.printIncomeCategories();
        }
        else if (choice == 5) {
            tracker.saveCategoriesToFile();
            std::cout << "��������� ��������� � ����." << std::endl;
        }
        else if (choice == 6) {
            std::string categoryName;
            double amount;
            std::cout << "������� �������� ���������, ��� ������� ������ �������� ����� ������: ";
            std::cin >> categoryName;
            std::cout << "������� ����� ����� ������: ";
            std::cin >> amount;
            tracker.updateExpenseCategoryAmount(categoryName, amount);
        }
        else if (choice == 7) {
            std::string categoryName;
            double amount;
            std::cout << "������� �������� ���������, ��� ������� ������ �������� ����� ������: ";
            std::cin >> categoryName;
            std::cout << "������� ����� ����� ������: ";
            std::cin >> amount;
            tracker.updateIncomeCategoryAmount(categoryName, amount);
        }
        else if (choice == 8) {
            std::string categoryName;
            std::cout << "������� �������� ���������, ������� ������ �������: ";
            std::cin >> categoryName;
            tracker.dellExpenseEntry(categoryName);
        }
        else if (choice == 9) {
            std::string categoryName;
            std::cout << "������� �������� ���������, ������� ������ �������: ";
            std::cin >> categoryName;
            tracker.dellIncomeEntry(categoryName);
        }
        else {
            std::cout << "�������� �����. ���������� ��� ���." << std::endl;
        }
    } while (choice != 10);

    return 0;
}