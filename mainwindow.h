#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_submitButton_clicked();
    void updateTimer();

private:
    Ui::MainWindow *ui;
    Game *game = nullptr;
    QTimer *timer = nullptr;
    int timeLeft = 10;
    void nextQuestion();
    void endGame();
};

#endif // MAINWINDOW_H 