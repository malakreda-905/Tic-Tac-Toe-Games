#ifndef GAME2_H
#define GAME2_H

#include <QDialog>

namespace Ui {
class game2;
}

class game2 : public QDialog
{
    Q_OBJECT

public:
    explicit game2(QWidget *parent = nullptr);
    ~game2();
private slots:
    void closeEvent(QCloseEvent *event);
    void handleCheckClick2(int i);
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    int is_win(int n);
    bool is_draw();
    void reset_push_buttons();
    void playRandomMove();
    void on_checkBox_2_clicked();
    void on_playButton_1_clicked();
    void resetAll();
    void on_checkBox_clicked();

    void on_resetButton_1_clicked();

private:
    Ui::game2 *ui;
};

#endif // GAME2_H
