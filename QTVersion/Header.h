#ifndef HEADER_H
#define HEADER_H
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QInputDialog>
#include <iostream>
#include <vector>
#include <QFile>
#include <QMainWindow>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>

class Category {
public:
    Category(const std::string& name, double amount);
    std::string getName() const;
    double getAmount() const;

private:
    std::string name;
    double amount;

};

class ExpenseTracker {
private:
    std::vector<Category> expenseCategories;
    std::vector<Category> incomeCategories;

public:
    ExpenseTracker();
    void addExpenseCategory(const std::string& categoryName, double amount);
    void addIncomeCategory(const std::string& categoryName, double amount);
    const std::vector<Category>& getExpenseCategories() const;
    const std::vector<Category>& getIncomeCategories() const ;
};

class IDataHandler
{
public:
    virtual void saveData(ExpenseTracker& tracker, const QString& filePath) = 0;
    virtual void loadData(ExpenseTracker& tracker, const QString& filePath, double &totalExpenses, double &totalIncome) = 0;
    virtual void saveCategory(QString Name, QString Amount, QString currentExpenseType, const QString& filePath) =0;
    virtual ~IDataHandler() = default;
};

class FileDataHandler : public IDataHandler
{
public:
    void saveData(ExpenseTracker& tracker, const QString& filePath) override;
    void saveCategory(QString Name, QString Amount ,QString currentExpenseType, const QString& filePath);
    void loadData(ExpenseTracker& tracker, const QString& filePath, double &totalExpenses, double &totalIncome) override ;
};

void loadCategoryName(ExpenseTracker& tracker, const QString& expenseCategories1, const QString& incomeCategories1 );

void saveCategoryName(const QString& Name,const QString& fileName);

#endif // HEADER_H
