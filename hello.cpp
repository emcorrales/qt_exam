#include <QApplication>
#include <QLabel>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

class FileOpenDialog : public QWidget{
    
public:

    FileOpenDialog(QWidget *parent = nullptr) : QWidget(parent) {
        setupUi();
    }
    
    private slots:
    void openFile() {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                                        tr("Sequencher Project Files (*.spf);;Common Assembly Format (*.caf);;All Readable (*);;Smaller than 500kb;;500kb or larger"));
        
        if (!filePath.isEmpty()) {
            // Handle the selected file
            qDebug("Selected File: %s", qPrintable(filePath));
        }
    }
    
    private slots:
    void onComboBoxIndexChanged(int index) {
        // Handle the selection change
        qDebug("Selected Index: %d", index);
    }
    
private:
    void setupUi() {
        QVBoxLayout *layout = new QVBoxLayout(this);
        
        QPushButton *openButton = new QPushButton(tr("Open File"), this);
        connect(openButton, &QPushButton::clicked, this, &FileOpenDialog::openFile);
        layout->addWidget(openButton);
        
        QLabel *label = new QLabel("Enable:");
        layout->addWidget(label);
        
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItem("Sequencher Projects");
        comboBox->addItem("CAF Projects");
        comboBox->addItem("All Readable");
        comboBox->addItem("Smaller than 500kb");
        comboBox->addItem("500kb or larger");
        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FileOpenDialog::onComboBoxIndexChanged);
        layout->addWidget(comboBox);
        
        setLayout(layout);
        setWindowTitle(tr("File Open Dialog"));
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    FileOpenDialog window;
    window.show();
    
    return app.exec();
}
