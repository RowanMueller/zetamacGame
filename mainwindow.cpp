#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::on_submitButton_clicked);
    ui->submitButton->setEnabled(false);
    ui->answerEdit->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
    if (game) delete game;
}

void MainWindow::on_startButton_clicked() {
    if (game) delete game;
    // For demo, use fixed settings. You can add UI for these.
    int min = 1, max = 10, duration = 60, mode = 1; // TODO: get from UI
    game = new Game(min, max, duration, mode);
    ui->scoreLabel->setText("0");
    timeLeft = 10;
    ui->timerLabel->setText(QString::number(timeLeft));
    ui->submitButton->setEnabled(true);
    ui->answerEdit->setEnabled(true);
    ui->startButton->setEnabled(false);
    nextQuestion();
    timer->start(1000); // 1 second interval
}

void MainWindow::nextQuestion() {
    game->nextQuestion();
    ui->questionLabel->setText(QString::fromStdString(game->getCurrentQuestion()));
    ui->answerEdit->clear();
    ui->answerEdit->setFocus();
    ui->scoreLabel->setText(QString::number(game->getScore()));
    timeLeft = 10;
    ui->timerLabel->setText(QString::number(timeLeft));
}

void MainWindow::on_submitButton_clicked() {
    bool ok;
    int userAnswer = ui->answerEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid integer answer.");
        return;
    }
    if (game->checkAnswer(userAnswer)) {
        nextQuestion();
    } else {
        QMessageBox::information(this, "Incorrect", "Incorrect answer. Try the next one!");
        nextQuestion();
    }
}

void MainWindow::updateTimer() {
    timeLeft--;
    ui->timerLabel->setText(QString::number(timeLeft));
    if (timeLeft <= 0) {
        timer->stop();
        endGame();
    }
}

void MainWindow::endGame() {
    ui->submitButton->setEnabled(false);
    ui->answerEdit->setEnabled(false);
    ui->startButton->setEnabled(true);
    QMessageBox::information(this, "Game Over", QString("Your score: %1").arg(game->getScore()));
} 