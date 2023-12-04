//
//  custom_dialog.cpp
//  hello_world
//
//  Created by Emmanuel Corrales on 12/4/23.
//

#include "custom_dialog.hpp"

using namespace Custom;


MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Choose a file");
    
    // Create a layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    initFileSystemModel();
    initTreeView(layout);
    initFileFiltersDropDown(layout);
    initActionDropDown(layout);
    initChooseFileButton(layout);
    setLayout(layout);
}

void MyDialog::initFileSystemModel(){
    mModel = new MyFileSystemModel(this);
    
    // Set the home path as default model.
    mModel->setRootPath(QDir::homePath());
    
    // Set spf as default filter.
    QStringList filters;
    filters << "*.spf";
    mModel->setNameFilters(filters);
    
    // Filter files greater than 500kb
    mModel->setMaxSize(SMALL_FILE_MAX_SIZE);
}

void MyDialog::initTreeView(QVBoxLayout *layout) {
    // Create a tree view and set the model
    mTreeView = new QTreeView(this);
    mTreeView->setModel(mModel);
    
    // Set the root index of the tree view to the root path index
    QModelIndex homeIndex = mModel->index(QDir::homePath());
    mTreeView->setRootIndex(homeIndex);
    
    layout->addWidget(mTreeView);
}

void MyDialog::initFileFiltersDropDown(QVBoxLayout *layout) {
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItem("Sequencher Projects");
    comboBox->addItem("CAF Projects");
    comboBox->addItem("All Readable");
    comboBox->addItem("Smaller than 500kb");
    comboBox->addItem("500kb or larger");
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyDialog::onFileFilterIndexChanged);
    
    layout->addWidget(comboBox);
}

void MyDialog::onFileFilterIndexChanged(int index) {
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

void MyDialog::initActionDropDown(QVBoxLayout *layout)
{
    QComboBox *actionDropDown = new QComboBox(this);
    actionDropDown->addItem("Original");
    actionDropDown->addItem("Copy");
    actionDropDown->addItem("Original Read-only");
    connect(actionDropDown, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MyDialog::onActionModeIndexChanged);
    layout->addWidget(actionDropDown);
}

void MyDialog::onActionModeIndexChanged(int index) {

    switch (index) {
        case ORIGINAL:
            break;
            
        case COPY:
            break;
            
        case READ_ONLY:
            break;
            
        default:
            break;
    }
    
    // Handle the selection change
    qDebug("Selected Index: %d", index);
}

void MyDialog::initChooseFileButton(QVBoxLayout *layout) {
    QPushButton *button = new QPushButton("Open");
    layout->addWidget(button);
}
