To open this project on Xcode, open the terminal and
navigate to the project directory.

Execute the command below:

qmake -project

Open the qt_exam.pro file and insert the following lines after the line:

INCLUDEPATH += .
QT += widgets

Execute the command below:

qmake -spec macx-xcode qt_exam.pro

You can now open this project in Xcode.