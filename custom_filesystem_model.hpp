//
//  custom_filesystem_model.hpp
//  hello_world
//
//  Created by Emmanuel Corrales on 12/3/23.
//

#ifndef custom_filesystem_model_hpp
#define custom_filesystem_model_hpp

#include <QApplication>
#include <QFileSystemModel>
#include <QTreeView>
#include <QDir>

#define SPF 0
#define CAF 1
#define ALL_READABLE 2
#define SMALL_FILE 3
#define LARGE_FILE 4

namespace Custom
{

class MyFileSystemModel : public QFileSystemModel
{
public:
    MyFileSystemModel(QObject* parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void setMaxSize(qint64 size);
    void setFileFilterMode(int filterMode);
    
private:
    qint64 maxSize = -1;
    int mFilterMode = SPF;
};

}
#endif /* custom_filesystem_model_hpp */
