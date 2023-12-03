//
//  custom_filesystem_model.cpp
//  hello_world
//
//  Created by Emmanuel Corrales on 12/3/23.
//

#include "custom_filesystem_model.hpp"
using namespace Custom;

MyFileSystemModel::MyFileSystemModel(QObject* parent): QFileSystemModel(parent)
{
}

Qt::ItemFlags MyFileSystemModel::flags(const QModelIndex& index) const {
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

void MyFileSystemModel::setMaxSize(qint64 size)
{
    maxSize = size;
}

void MyFileSystemModel::setFileFilterMode(int filterMode)
{
    mFilterMode = filterMode;
}
