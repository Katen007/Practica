
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
#include <QMessageBox>
#include <QFileDialog>
class Category {
public:
    Category(const std::string& name, double amount) : name(name), amount(amount) {}
    std::string getName() const { return name; }

private:
    std::string name;
    double amount;

};


class ExpenseTracker {
private:
    std::vector<Category> expenseCategories;
    std::vector<Category> incomeCategories;

public:
    ExpenseTracker() {

        expenseCategories = {
            Category("Еда", 0.0),
            Category("Одежда", 0.0),
            Category("Машина", 0.0)
        }
        ;
        incomeCategories = {
                            Category("Работа", 0.0),
                            Category("Хобби", 0.0),

        };}
    void addExpenseCategory(const std::string& categoryName, double amount) {
        expenseCategories.push_back(Category(categoryName, amount));
    }

    void addIncomeCategory(const std::string& categoryName, double amount) {
        incomeCategories.push_back(Category(categoryName, amount));
    }

    const std::vector<Category>& getExpenseCategories() const {
        return expenseCategories;
    }

    const std::vector<Category>& getIncomeCategories() const {
        return incomeCategories;
    }
};
void loadCategoriesFromFile(ExpenseTracker& tracker, const QString& filename,double &totalExpenses, double & totalIncome) {
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
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
                //std::cout<<type<<std::endl;
                //tracker.addExpenseCategory(categoryName.toStdString(), amount);
                // Add to income categories as needed
            }
        }
        file.close();
    } else {

    }
}

int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "Russian");
    ExpenseTracker tracker;

    QApplication app(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;

    QPushButton *startButton = new QPushButton("Начать");
    QPushButton *exitButton = new QPushButton("Выход");
    QLabel *typeLabel = new QLabel("Выберите тип операции:");
    QComboBox *typeComboBox = new QComboBox;
    QPushButton *showBalanceButton = new QPushButton("Показать баланс");
    typeComboBox->addItem("Расход");
    typeComboBox->addItem("Доход");


    QLabel *categoryLabel = new QLabel("Выберите категорию:");
    QComboBox *categoryComboBox = new QComboBox;

    QLabel *amountLabel = new QLabel("Введите сумму:");
    QLineEdit *amountInput = new QLineEdit;

    QPushButton *addCategoryButton = new QPushButton("Добавить категорию");

  QFile expenseFile("C:/Users/vilen/Downloads/expense.txt");
     QString expenseFile1;
  QMessageBox msgBox(QMessageBox::Question, "Выбор кошелька",
                     "Создать новый кошелек или продолжить старый?",
                     QMessageBox::Yes | QMessageBox::No);

  // Set default button
  msgBox.setDefaultButton(QMessageBox::Yes);

  // Get button pointers and change text
  QAbstractButton* yesButtonAbstract = msgBox.button(QMessageBox::Yes);
  QPushButton* yesButton = dynamic_cast<QPushButton*>(yesButtonAbstract);
  if (yesButton) { // Check if cast is successful
      yesButton->setText("Create New");
  }
  double totalExpenses = 0.0;
  double totalIncome = 0.0;

  QAbstractButton* noButtonAbstract = msgBox.button(QMessageBox::No);
  QPushButton* noButton = dynamic_cast<QPushButton*>(noButtonAbstract);
  if (noButton) { // Check if cast is successful
      noButton->setText("Continue Old");
  }

  // Convert the return value to QMessageBox::StandardButton
     int ret = msgBox.exec();
      QMessageBox::StandardButton reply;
  switch (ret) {
  case QMessageBox::Yes:
      reply = QMessageBox::Yes;
      break;
  case QMessageBox::No:
      reply = QMessageBox::No;
      break;
  // ... (handle other cases like Cancel, Close, etc. if needed) ...
  default:
      // Handle unexpected return values
      break;
  }
    if (reply == QMessageBox::Yes) {
        // Create new wallet
        expenseFile1 = QFileDialog::getSaveFileName(
            nullptr, "Сохранить файл кошелька", "", "Text Files (*.txt)");
        if (expenseFile1.isEmpty()) { // Check if QString is empty
            return 1; // Cancel if no file selected
        }
    } else {
        // Continue old wallet
        expenseFile1 = QFileDialog::getOpenFileName(
            nullptr, "Открыть файл кошелька", "", "Text Files (*.txt)");
        if (expenseFile1.isEmpty()) { // Check if QString is empty
            return 1; // Cancel if no file selected
        }
        loadCategoriesFromFile(tracker, expenseFile1,totalExpenses,totalIncome); // Load categories from file
    }

    const std::string expenses = "Расходы: "+std::to_string(int(totalExpenses));
    const std::string income = "Доходы: "+std::to_string(int(totalIncome));
    QLabel *expensesLabel = new QLabel(QString::fromStdString(expenses));
    QLabel *incomeLabel = new QLabel(QString::fromStdString(income));
    auto updateCounters = [&]() {
        expensesLabel->setText("Расходы: " + QString::number(totalExpenses));
        incomeLabel->setText("Доходы: " + QString::number(totalIncome));
    };
    categoryLabel->setEnabled(false);
    categoryComboBox->setEnabled(false);
    amountLabel->setEnabled(false);
    amountInput->setEnabled(false);

    layout->addWidget(typeLabel);
    layout->addWidget(typeComboBox);
    layout->addWidget(categoryLabel);
    layout->addWidget(categoryComboBox);
    layout->addWidget(amountLabel);
    layout->addWidget(amountInput);
    layout->addWidget(addCategoryButton);
    layout->addWidget(startButton);
    layout->addWidget(exitButton);
    layout->addWidget(expensesLabel);
    layout->addWidget(incomeLabel);
    layout->addWidget(showBalanceButton);
    window.setLayout(layout);
    window.show();


    // Function to update expense and income labels

    bool startClicked = false;
QString currentExpenseType = "Расход";
    QObject::connect(typeComboBox, &QComboBox::currentTextChanged, [&](const QString &text){
        currentExpenseType = text;
    });
    QObject::connect(startButton, &QPushButton::clicked, [&](){
        startClicked = true;
         // Запретить изменение типа операции после начала
        categoryLabel->setEnabled(true);
        categoryComboBox->setEnabled(true);
        amountLabel->setEnabled(true);
        amountInput->setEnabled(true);

        if (typeComboBox->currentText() == "Расход") {
            // Заполнить список категорий расходов
            categoryComboBox->clear();
            for (const Category& cat : tracker.getExpenseCategories()) {
                categoryComboBox->addItem(QString::fromStdString(cat.getName()));
            }
        } else if (typeComboBox->currentText() == "Доход") {
            // Заполнить список категорий доходов
            categoryComboBox->clear();
            for (const Category& cat : tracker.getIncomeCategories()) {
                categoryComboBox->addItem(QString::fromStdString(cat.getName()));
            }
        }
    });

    QObject::connect(exitButton, &QPushButton::clicked, [&](){
        app.exit();
    });

    QObject::connect(addCategoryButton, &QPushButton::clicked, [&](){
        bool ok;
        QString newCategoryName = QInputDialog::getText(&window, "Добавить категорию", "Введите название новой категории:", QLineEdit::Normal, "", &ok);
        if (ok && !newCategoryName.isEmpty()) {
            if (typeComboBox->currentText() == "Расход") {
                tracker.addExpenseCategory(newCategoryName.toStdString(), 0.0);
            } else if (typeComboBox->currentText() == "Доход") {
                tracker.addIncomeCategory(newCategoryName.toStdString(), 0.0);
            }
        }
    });

    QObject::connect(showBalanceButton, &QPushButton::clicked, [&]() {
        double balance = totalIncome - totalExpenses;
        QMessageBox::information(&window, "Баланс", "Текущий баланс: " + QString::number(balance));
    });

    // Connect Enter key press in amountInput
    QObject::connect(amountInput, &QLineEdit::returnPressed,  [&]() {
        if (!startClicked) return;

        QString category = categoryComboBox->currentText();
        QString amountText = amountInput->text();

        bool conversionOk;
        double amount = amountText.toDouble(&conversionOk);
        if (!conversionOk) {
            // Handle invalid amount input (e.g., show an error message)
            return;
        }
        if (currentExpenseType == "Расход") {
            totalExpenses += amount;
        } else if (currentExpenseType == "Доход") {
            totalIncome += amount;
        }
        updateCounters();
        // Determine expense type (assuming you have a way to do this)
         // Replace with your logic to determine if it's an expense

        // Write to file
        if (expenseFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&expenseFile);
            out << category << "," << amount << "," << currentExpenseType << "\n";
            expenseFile.close();
        } else {
            // Handle file opening error
        }

        // Clear input fields (optional)
        amountInput->clear();
        // ... (you might want to clear the category selection as well) ...
    });

    return app.exec();
}

