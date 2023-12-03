#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDir>
#include <QVBoxLayout>
#include <QComboBox>

#define SPF 0
#define CAF 1
#define ALL_READABLE 2
#define SMALL_FILE 3
#define LARGE_FILE 4

#define SMALL_FILE_MAX_SIZE 500 * 1024

class CustomFileSystemModel : public QFileSystemModel
{
public:
    CustomFileSystemModel(QObject* parent = nullptr)
    : QFileSystemModel(parent)
    {
    }
    
    Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        Qt::ItemFlags defaultFlags = QFileSystemModel::flags(index);
        
        // Disable specific items (e.g., files with size > maxSize)
        qint64 fileSize = fileInfo(index).size();
        
        
        if (fileSize > maxSize && mFilterMode == SMALL_FILE) {
            return defaultFlags & ~Qt::ItemIsEnabled;
        } else if (mFilterMode == LARGE_FILE && fileSize < maxSize) {
            return defaultFlags & ~Qt::ItemIsEnabled;
        }
        
        return defaultFlags;
    }
    
    void setMaxSize(qint64 size)
    {
        maxSize = size;
    }
    
    void setFileFilterMode(int filterMode)
    {
        mFilterMode = filterMode;
    }
    
private:
    qint64 maxSize = -1;
    int mFilterMode = SPF;
};

class MyWidget : public QWidget
{
public:
    MyWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Create a layout
        QVBoxLayout *layout = new QVBoxLayout(this);
        
        // Create a custom file system model
        mModel = new CustomFileSystemModel(this);
        
        // Set the home path as default model.
        QString homePath = QDir::homePath(); // Change this to your desired directory
        mModel->setRootPath(homePath);
        
        // Set spf as default filter.
        QStringList filters;
        filters << "*.spf";
        mModel->setNameFilters(filters);
        
        // Create a tree view and set the model
        mTreeView = new QTreeView(this);
        mTreeView->setModel(mModel);
        
        // Set the root index of the tree view to the root path index
        QModelIndex homeIndex = mModel->index(homePath);
        mTreeView->setRootIndex(homeIndex);
        
        // Set a maximum file size for filtering (adjust as needed)
        mModel->setMaxSize(SMALL_FILE_MAX_SIZE); // Filter files greater than 500kb
        layout->addWidget(mTreeView);
        
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItem("Sequencher Projects");
        comboBox->addItem("CAF Projects");
        comboBox->addItem("All Readable");
        comboBox->addItem("Smaller than 500kb");
        comboBox->addItem("500kb or larger");
        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyWidget::onComboBoxIndexChanged);
        layout->addWidget(comboBox);
        
        QComboBox *actionComboBox = new QComboBox(this);
        actionComboBox->addItem("Original");
        actionComboBox->addItem("Copy");
        actionComboBox->addItem("Original Read-only");
        connect(actionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyWidget::onOpenModeIndexChanged);
        layout->addWidget(actionComboBox);
        
        // Set the layout for the widget
        setLayout(layout);
    }
    
private:
    QTreeView *mTreeView;
    CustomFileSystemModel *mModel;
    
    
    private slots:
    void onComboBoxIndexChanged(int index) {
        QStringList filters;

        switch (index) {
            case SPF:
                filters << "*.spf";
                mModel->setFileFilterMode(SPF);
                break;
                
            case CAF:
                filters << "*.caf";
                mModel->setFileFilterMode(CAF);
                break;
                
            case ALL_READABLE:
                filters << "*.spf";
                filters << "*.caf";
                mModel->setFileFilterMode(ALL_READABLE);
                break;
                
            case SMALL_FILE:
                filters = QStringList();
                mModel->setFileFilterMode(SMALL_FILE);
                break;
                
            case LARGE_FILE:
                filters = QStringList();
                mModel->setFileFilterMode(LARGE_FILE);
                break;
                
            default:
                break;
        }
        
        mModel->setNameFilters(filters);
        
        // Handle the selection change
        qDebug("Selected Index: %d", index);
    }
    
    private slots:
    void onOpenModeIndexChanged(int index) {
        
        // Handle the selection change
        qDebug("Selected Index: %d", index);
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    MyWidget widget;
    widget.show();
    
    return app.exec();
}
