#include "Header.h"

Category::Category(const std::string& name, double amount) : name(name), amount(amount) {}

std::string Category::getName() const { return name; }

double Category::getAmount() const { return amount; }


ExpenseTracker::ExpenseTracker() {
    expenseCategories = {};
    incomeCategories = {};
}
void ExpenseTracker::addExpenseCategory(const std::string& categoryName, double amount) {
    expenseCategories.push_back(Category(categoryName, amount));
}

void ExpenseTracker::addIncomeCategory(const std::string& categoryName, double amount) {
    incomeCategories.push_back(Category(categoryName, amount));
}

const std::vector<Category>& ExpenseTracker::getExpenseCategories() const {
    return expenseCategories;
}

const std::vector<Category>& ExpenseTracker::getIncomeCategories() const {
    return incomeCategories;
}

void FileDataHandler::saveData(ExpenseTracker& tracker, const QString& filePath)  {
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    file.close();
}
void FileDataHandler::saveCategory(QString Name, QString Amount ,QString currentExpenseType, const QString& filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }
    QTextStream out(&file);
    out << Name << "," << Amount << "," << currentExpenseType << "\n";
    file.close();
}

void FileDataHandler::loadData(ExpenseTracker& tracker, const QString& filePath, double &totalExpenses, double &totalIncome) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() == 3) {
            double amount = parts[1].toDouble();
            std::string type=parts[2].toStdString();
            if (type=="Расход"){
                totalExpenses+=amount;
            }
            else{
                totalIncome+=amount;
            }
        }
    }
    file.close();
}


void loadCategoryName(ExpenseTracker& tracker, const QString& expenseCategories1, const QString& incomeCategories1 ){
    QFile ExpenseFile(expenseCategories1);
    if (!ExpenseFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    QTextStream in(&ExpenseFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        tracker.addExpenseCategory(line.toStdString(), 0.0);
    }
    ExpenseFile.close();

    QFile IncomeFile(incomeCategories1);
    if (!IncomeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    QTextStream in2(&IncomeFile);
    while (!in2.atEnd()) {
        QString line = in2.readLine();
        tracker.addIncomeCategory(line.toStdString(), 0.0);
    }
    IncomeFile.close();
}

void saveCategoryName(const QString& Name,const QString& fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }
    QTextStream out(&file);
    out << Name << "\n";
    file.close();

}
