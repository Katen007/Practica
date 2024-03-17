#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <vector>

class Category {
public:
    Category(const std::string& name, double amount) : name(name), amount(amount) {}
private:
    std::string name;
    double amount;
};

class ExpenseTracker {
private:
    std::vector<Category> expenseCategories;
    std::vector<Category> incomeCategories;

public:
    void addExpenseCategory(const std::string& categoryName, double amount) {
        expenseCategories.push_back(Category(categoryName, amount));
    }
};

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    ExpenseTracker tracker;

    QApplication app(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;

    QPushButton *startButton = new QPushButton("Начать");
    QPushButton *exitButton = new QPushButton("Выход");
    QLabel *categoryLabel = new QLabel("Введите название новой категории расходов:");
    QLabel *amountLabel = new QLabel("Введите сумму затрат для этой категории:");
    QLineEdit *categoryInput = new QLineEdit;
    QLineEdit *amountInput = new QLineEdit;

    categoryInput->setEnabled(false);
    amountInput->setEnabled(false);

    layout->addWidget(categoryLabel);
    layout->addWidget(categoryInput);
    layout->addWidget(amountLabel);
    layout->addWidget(amountInput);
    layout->addWidget(startButton);
    layout->addWidget(exitButton);

    window.setLayout(layout);
    window.show();

    bool startClicked = false;

    QObject::connect(startButton, &QPushButton::clicked, [&](){
        startClicked = true;
        categoryInput->setEnabled(true);
        amountInput->setEnabled(true);
    });

    QObject::connect(exitButton, &QPushButton::clicked, [&](){
        app.exit();
    });

    QObject::connect(categoryInput, &QLineEdit::returnPressed, [&](){
        if (startClicked) {
            std::string categoryName = categoryInput->text().toStdString();
            double amount = amountInput->text().toDouble();
            tracker.addExpenseCategory(categoryName, amount);
            categoryInput->clear();
            amountInput->clear();
        }
    });

    return app.exec();
}
