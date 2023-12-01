#include <QApplication>
#include <QFileDialog>
#include <QPushButton>
#include <QVBoxLayout>

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
    
private:
    void setupUi() {
        QVBoxLayout *layout = new QVBoxLayout(this);
        
        QPushButton *openButton = new QPushButton(tr("Open File"), this);
        connect(openButton, &QPushButton::clicked, this, &FileOpenDialog::openFile);
        layout->addWidget(openButton);

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
