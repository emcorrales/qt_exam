//
//  custom_dialog.hpp
//  hello_world
//
//  Created by Emmanuel Corrales on 12/4/23.
//

#ifndef custom_dialog_hpp
#define custom_dialog_hpp



#include <QTreeView>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>

#define ORIGINAL 0
#define COPY 1
#define READ_ONLY 2

#include "custom_filesystem_model.hpp"

#define SMALL_FILE_MAX_SIZE 500 * 1024


namespace Custom {

class MyDialog : public QDialog
{
public:
    MyDialog(QWidget *parent = nullptr);
    
private slots:
void onComboBoxIndexChanged(int index);
    
private:
    void initFileSystemModel();
    void initTreeView(QVBoxLayout *layout);
    void initFileFiltersDropDown(QVBoxLayout *layout);
    void onFileFilterIndexChanged(int index);
    void initActionDropDown(QVBoxLayout *layout);
    void onActionModeIndexChanged(int index);
    void initChooseFileButton(QVBoxLayout *layout);
    
    QTreeView *mTreeView;
    MyFileSystemModel *mModel;
};

}

#endif /* custom_dialog_hpp */
