#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDir>
#include <QVBoxLayout>
#include <QComboBox>
#include <QRegularExpression>

class CustomFileSystemModel : public QFileSystemModel
{
public:
    CustomFileSystemModel(QObject* parent = nullptr)
    : QFileSystemModel(parent)
    {
    }
    
    CustomFileSystemModel(const QRegularExpression &nameFilterRegex, QObject *parent = nullptr)
    : QFileSystemModel(parent), nameFilterRegex(nameFilterRegex)
    {
    }
    
    QVariant data(const QModelIndex& index, int role) const override
    {
        if (role == Qt::SizeHintRole) {
            // Filter files based on size.
            qint64 fileSize = fileInfo(index).size();
            if (fileSize <= maxSize) {
                return QFileSystemModel::data(index, role);
            } else {
                return QVariant();
            }
        } else if (role == Qt::DisplayRole || role == Qt::EditRole) {
            // Only display files that match the name filter regex
            if (index.isValid() && !isDir(index)) {
                QString fileName = QFileSystemModel::data(index, QFileSystemModel::FileNameRole).toString();
                if (nameFilterRegex.match(fileName).hasMatch()) {
                    return fileName;
                } else {
                    return QVariant(); // Hide files that don't match the regex
                }
            }
        }
        return QFileSystemModel::data(index, role);
    }
    
    Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        Qt::ItemFlags defaultFlags = QFileSystemModel::flags(index);
        
        // Disable specific items (e.g., files with size > maxSize)
        qint64 fileSize = fileInfo(index).size();
        if (fileSize > maxSize) {
            return defaultFlags & ~Qt::ItemIsEnabled;
        }
        
        return defaultFlags;
    }
    
    void setMaxSize(qint64 size)
    {
        maxSize = size;
    }
    
private:
    qint64 maxSize = -1;
    QRegularExpression nameFilterRegex;
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
        
        // Create a tree view and set the model
        mTreeView = new QTreeView(this);
        mTreeView->setModel(mModel);
        
        // Set the root index of the tree view to the root path index
        QModelIndex homeIndex = mModel->index(homePath);
        mTreeView->setRootIndex(homeIndex);
        
        // Set a maximum file size for filtering (adjust as needed)
        mModel->setMaxSize(50 * 1024); // Filter files greater than 1 MB
        layout->addWidget(mTreeView);
        
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItem("Sequencher Projects");
        comboBox->addItem("CAF Projects");
        comboBox->addItem("All Readable");
        comboBox->addItem("Smaller than 500kb");
        comboBox->addItem("500kb or larger");
        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyWidget::onComboBoxIndexChanged);
        layout->addWidget(comboBox);
        
        // Set the layout for the widget
        setLayout(layout);
    }
    
private:
    QTreeView *mTreeView;
    CustomFileSystemModel *mModel;
    
    private slots:
    void onComboBoxIndexChanged(int index) {
        // Create a regular expression for filtering file names (e.g., ".*\\.txt")
        QRegularExpression nameFilterRegex(".*\\.txt");
        
        // Create a custom file system model with the specified name filter regex
        CustomFileSystemModel *model = new CustomFileSystemModel(nameFilterRegex);
        
        // Set the root path to the directory you want to display
        QString homePath = QDir::homePath(); // Change this to your desired directory
        model->setRootPath(homePath);
        
        switch (index) {
            case 0:
                
                break;
                
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
                
            default:
                break;
        }
        
        mTreeView->setModel(model);
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
