#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDir>

class CustomFileSystemModel : public QFileSystemModel
{
public:
    CustomFileSystemModel(QObject* parent = nullptr)
    : QFileSystemModel(parent)
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
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    // Create a custom file system model
    CustomFileSystemModel model;
    
    // Set the home path as default model.
    QString homePath = QDir::homePath(); // Change this to your desired directory
    model.setRootPath(homePath);
    
    // Create a tree view and set the model
    QTreeView treeView;
    treeView.setModel(&model);
    
    // Set the root index of the tree view to the root path index
    QModelIndex homeIndex = model.index(homePath);
    treeView.setRootIndex(homeIndex);
    
    // Set a maximum file size for filtering (adjust as needed)
    model.setMaxSize(50 * 1024); // Filter files greater than 1 MB
    
    // Show the tree view
    treeView.show();
    
    return app.exec();
}
