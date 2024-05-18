#include "Header.h"

int main(int argc, char *argv[]) {
    setlocale (LC_ALL, "Russian");
    ExpenseTracker tracker;

    QApplication app(argc, argv);
    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout;

    QPushButton *startButton = new QPushButton("Начать");
    QPushButton *exitButton = new QPushButton("Выход");
    QPushButton *statButton = new QPushButton("История");
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

    IDataHandler* dataHandler = new FileDataHandler();

    QFile expenseFile        ("D:/qt/build-untitled-Desktop_Qt_shared_MinGW_w64_MINGW64_MSYS2-Debug/pay.txt");
    QString expenseCategories("D:/qt/build-untitled-Desktop_Qt_shared_MinGW_w64_MINGW64_MSYS2-Debug/expenseCategories.txt");
    QString incomeCategories ("D:/qt/build-untitled-Desktop_Qt_shared_MinGW_w64_MINGW64_MSYS2-Debug/incomeCategories.txt");

    loadCategoryName(tracker, expenseCategories, incomeCategories);
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
        expenseFile.setFileName(expenseFile1);
        if (!expenseFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(nullptr, "Ошибка", "Не удалось создать файл.");
            return 1;
        }
        expenseFile.close(); // Закрываем файл после создания.
    } else {
        // Continue old wallet
        expenseFile1 = QFileDialog::getOpenFileName(
            nullptr, "Открыть файл кошелька", "", "Text Files (*.txt)");
        if (expenseFile1.isEmpty()) { // Check if QString is empty
            return 1; // Cancel if no file selected
        }
        expenseFile.setFileName(expenseFile1);
        dataHandler->loadData(tracker, expenseFile1,totalExpenses,totalIncome);
        //loadCategoriesFromFile(tracker, expenseFile1,totalExpenses,totalIncome);
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
    layout->addWidget(statButton);
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
                saveCategoryName(newCategoryName, expenseCategories);

            } else if (typeComboBox->currentText() == "Доход") {
                tracker.addIncomeCategory(newCategoryName.toStdString(), 0.0);
                saveCategoryName(newCategoryName, incomeCategories);
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

        QString name = categoryComboBox->currentText();
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

        dataHandler->saveCategory(name,amountText, currentExpenseType, expenseFile1);

        // Clear input fields (optional)
        amountInput->clear();
        // ... (you might want to clear the category selection as well) ...
    });
    QMainWindow *newWindow = new QMainWindow;
    newWindow->setWindowTitle("Содержимое файла");

    // Создать текстовое поле для нового окна
    QTextEdit *newTextEdit = new QTextEdit;
    newTextEdit->setReadOnly(true);

    // Разместить текстовое поле в новом окне
    newWindow->setCentralWidget(newTextEdit);

    QObject::connect(statButton, &QPushButton::clicked, [&]() {
        // Открыть диалоговое окно для выбора файла
        QString fileName = expenseFile1;

        if (!fileName.isEmpty()) {
            // Открыть файл для чтения
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::Text)) {
                // Создать входной текстовый поток
                QTextStream in(&file);

                // Считать содержимое файла
                QString text = in.readAll();

                // Закрыть файл
                file.close();

                // Если новое окно еще не открыто, открыть его и установить содержимое текстового поля
                newWindow->close();
                newWindow->show();
                newTextEdit->setPlainText(text);

            } else {
                // Сообщить об ошибке
                qCritical() << "Не удалось открыть файл для чтения";
            }
        }
    });
    return app.exec();
}
