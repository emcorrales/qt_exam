#include <QApplication>
#include "custom_dialog.hpp"
using namespace Custom;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    MyDialog dialog ;
    dialog.show();
    
    return app.exec();
}
