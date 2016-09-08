#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <vector>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace Ui {
class Assembler;
}

class Assembler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Assembler(QWidget *parent = 0);
    ~Assembler();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_textEdit_selectionChanged();

private:
    Ui::Assembler *ui;
};

#endif // ASSEMBLER_H
