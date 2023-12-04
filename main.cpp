#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include "custom_dialog.hpp"

using namespace Custom;

class MainWindow : public QWidget {

public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setupUi();
    }

private slots:
    void onButtonClick() {
            MyDialog dialog ;
            dialog.exec();
    }

private:
    void setupUi() {
        QPushButton *button = new QPushButton("Click me!", this);
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClick);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(button);

        setLayout(layout);
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
        
    MainWindow mainWindow;
    mainWindow.show();

    
    return app.exec();
}
