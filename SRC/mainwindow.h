#pragma once

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();

private:
    QTextEdit *textEdit;
};
