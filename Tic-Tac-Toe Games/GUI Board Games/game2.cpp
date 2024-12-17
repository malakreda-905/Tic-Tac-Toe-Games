#include "game2.h"
#include "ui_game2.h"
#include <qmessagebox.h>
#include <QCloseEvent>
#include <QRandomGenerator>
#include <QTimer>
game2::game2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::game2)
{
    ui->setupUi(this);
    // get only 1 upper case char for symbol input
    ui->player1Symbol_1->setMaxLength(1);
    ui->player2Symbol_1->setMaxLength(1);
    connect(ui->player1Symbol_1, &QLineEdit::textChanged, this, [=](const QString &text) {
        if (!text.isEmpty()) {
            QString upperText = text.left(1).toUpper(); // Convert to uppercase
            ui->player1Symbol_1->setText(upperText);
        }
    });
    connect(ui->player2Symbol_1, &QLineEdit::textChanged, this, [=](const QString &text) {
        if (!text.isEmpty()) {
            QString upperText = text.left(1).toUpper(); // Convert to uppercase
            ui->player2Symbol_1->setText(upperText);
        }
    });
    ///////////////////////////////////////////////
    // disable some items
    ui->resetButton_1->hide();
    ui->Board->setEnabled(false);
    ui->gameStarted->hide();
    ui->winB->hide();
    ui->pts->hide();
    ///////////////////////////////////////////////
}
QString player11XName, player22XName, player11Symbol, player22Symbol;
bool  currPlayer11 = true, player11Random = false, player22Random = false;
int nmoves = 0, player1Score = 0, player2Score = 0;
void game2::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept(); // Allow the window to close
        on_resetButton_1_clicked();
    } else {
        event->ignore(); // Ignore the close event
    }
}

void game2::reset_push_buttons(){
    for (int i = 0; i <= 8; ++i) {
            QString buttonName = QString("pushButton_%1").arg(i);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if (button) {
                button->setText("");
                button->setEnabled(true);
            }
        }
}

void game2::resetAll(){
    player11Random = false;
    player22Random = false;
    ui->resetButton_1->hide();
    ui->player1Card_1->show();
    ui->player2Card_1->show();
    ui->p1->show();
    ui->p2->show();
    ui->checkBox->show();
    ui->checkBox_2->show();
    ui->pts->setText("");
    ui->pts->hide();
    ui->winB->hide();
    ui->gameStarted->hide();
    ui->gameStarted->setText("");
    ui->playButton_1->show();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->player1Name_1->clear();
    ui->player1Symbol_1->clear();
    ui->player2Name_1->clear();
    ui->player2Symbol_1->clear();
    ui->Board->setEnabled(false);
    ui->p1S->hide();
    ui->p2S->hide();
    ui->p1S->clear();
    ui->p2S->clear();
    reset_push_buttons();
    nmoves = 0, player1Score = 0, player2Score = 0;
    currPlayer11 = true;
}
game2::~game2()
{
    delete ui;
}

void game2::playRandomMove()
{
    QVector<int> availableMoves; // Vector to store indices of empty buttons

    // Iterate through all buttons (indices 0 to 8) to find empty ones
    for (int i = 0; i < 9; ++i) {
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(i));
        if (button && button->text().isEmpty()) {
            availableMoves.append(i);
        }
    }

    // If there are no available moves, return (game is likely over)
    if (availableMoves.isEmpty()) {
        return;
    }

    // Select a random index from the available moves
    int randomIndex = QRandomGenerator::global()->bounded(availableMoves.size());
    int chosenMove = availableMoves[randomIndex];

    handleCheckClick2(chosenMove);
}


void game2::on_playButton_1_clicked()
{
    nmoves = 0, player1Score = 0, player2Score = 0;
    player11XName = ui->player1Name_1->text();
    player22XName = ui->player2Name_1->text();
    player11Symbol = ui->player1Symbol_1->text().toUpper();
    player22Symbol = ui->player2Symbol_1->text().toUpper();
    // check if names is valid or not
    if (player11XName.size() == 0 ){
        ui->validName1_1->setText("not valid !");
        if (ui->validName1_1->isHidden()) ui->validName1_1->show();
    }
    else if (!ui->validName1_1->isHidden()){
        ui->validName1_1->clear();
        ui->validName1_1->hide();
    }
    if (player22XName.size() == 0){
        ui->validName2_1->setText("not valid !");
        if (ui->validName2_1->isHidden()) ui->validName2_1->show();
    }
    else if (!ui->validName2_1->isHidden()){
        ui->validName2_1->clear();
        ui->validName2_1->hide();
    }
    // set valid symbols
    if (player11Symbol.size() == 0 || !(player11Symbol == "S" || player11Symbol == "U")){
        if (player11Symbol.size()){
            ui->validSymbol1_1->setText("Only S or U.");
        }else
            ui->validSymbol1_1->setText("not valid !");
        if (ui->validSymbol1_1->isHidden()) ui->validSymbol1_1->show();
    }
    else if (!ui->validSymbol1_1->isHidden()){
        ui->validSymbol1_1->clear();
        ui->validSymbol1_1->hide();
    }
    if (player22Symbol.size() == 0 || !(player22Symbol == "S" || player22Symbol == "U")){
        if (player22Symbol.size()){
            ui->validSymbol2_1->setText("Only S or U.");
        }else
            ui->validSymbol2_1->setText("not valid !");
        if (ui->validSymbol2_1->isHidden()) ui->validSymbol2_1->show();
    }
    else if (player22Symbol == player11Symbol){
        ui->validSymbol2_1->setText("choose another char please !");
        if (ui->validSymbol2_1->isHidden()) ui->validSymbol2_1->show();
    }
    else if (!ui->validSymbol2_1->isHidden()){
        ui->validSymbol2_1->clear();
        ui->validSymbol2_1->hide();
    }
    /////////////////////////////////
    bool allValid = player11XName.size() && player22XName.size() && player11Symbol.size() && player22Symbol.size() && player11Symbol != player22Symbol && (player11Symbol == "S" || player11Symbol == "U") && (player22Symbol == "S" || player22Symbol == "U");
    // check if all valid run the game
    if (allValid){
        player11Random = ui->checkBox->isChecked();
        player22Random = ui->checkBox_2->isChecked();
        ui->resetButton_1->show();
        ui->player1Card_1->hide();
        ui->player2Card_1->hide();
        ui->p1->hide();
        ui->p2->hide();
        ui->checkBox->hide();
        ui->checkBox_2->hide();
        ui->pts->setText("Player " + (currPlayer11 ? player11XName: player22XName) + " Trun");
        ui->pts->show();
        ui->gameStarted->show();
        ui->gameStarted->setText("Game Started..");
        ui->playButton_1->hide();
        ui->Board->setEnabled(true);
        ui->p1S->show();
        ui->p2S->show();
        if (player11Random) QTimer::singleShot(500, this, &game2::playRandomMove); // Add a delay for better UX

    }

}

void game2::on_checkBox_clicked()
{
    if (player11Random){
        player11Random = false;
        ui->player1Name_1->setText("");
        ui->player1Symbol_1->setText("");
    }else{
        player11Random = true;
        ui->player1Name_1->setText("Random Player 1");
        ui->player1Symbol_1->setText("S");
    }
}


void game2::on_checkBox_2_clicked()
{
    if (player22Random){
        player22Random = false;
        ui->player2Name_1->setText("");
        ui->player2Symbol_1->setText("");
    }else{
        player22Random = true;
        ui->player2Name_1->setText("Random Player 2");
        ui->player2Symbol_1->setText("U");
    }
}
bool game2::is_draw(){return false;}
void game2::handleCheckClick2(int i)
{
    // Find the button based on its name
    QPushButton *clickedButton = findChild<QPushButton*>(QString("pushButton_%1").arg(i));
    if (!clickedButton || !clickedButton->isEnabled())
        return;

    // Set the button's text to "S" or "U" based on the current player
    QString move = currPlayer11 ? "S" : "U";
    clickedButton->setText(move);
    clickedButton->setEnabled(false);  // Disable the button

    // Check for a winning "S-U-S" sequence
    if (is_win(i)) {
        if (currPlayer11)
            player1Score++;
        else
            player2Score++;
    }
    ui->p1S->setText("Plyaer " + player11XName + " Score is " + QString::number(player1Score));
    ui->p2S->setText("Plyaer " + player22XName + " Score is " + QString::number(player2Score));
    nmoves++;

    // Switch players
    if (nmoves == 9){
        if (player1Score > player2Score) {
            ui->winB->setText("S");
            ui->pts->setText("Player " + player11XName+ " Won !");
            ui->gameStarted->setText("Game Ended.");
}
        else if (player1Score < player2Score) {
            ui->winB->setText("U");
            ui->pts->setText("Player " + player22XName+ " Won !");
            ui->gameStarted->setText("Game Ended.");
}
        else{
            ui->winB->setText("D");
            ui->pts->setText("Draw!");
            ui->gameStarted->setText("Game Over!");
        }
ui->winB->show();
return;

    }else{
        currPlayer11 = !currPlayer11;
        ui->pts->setText("Player " + (currPlayer11 ? player11XName: player22XName) + " Trun");
    }
    if (currPlayer11 && player11Random)     QTimer::singleShot(500, this, &game2::playRandomMove); // Add a delay for better UX

    if (!currPlayer11 && player22Random) QTimer::singleShot(500, this, &game2::playRandomMove); // Add a delay for better UX


}


int game2::is_win(int n)
{
    // Lambda to get button text based on row/column
    auto getButtonText = [&](int row, int col) -> QString {
        int index = row * 3 + col;
        QPushButton *button = findChild<QPushButton*>(QString("pushButton_%1").arg(index));
        return button ? button->text() : "";
    };

    int row = n / 3; // Determine the current row
    int col = n % 3; // Determine the current column

    // Check current row
    if (getButtonText(row, 0) == "S" && getButtonText(row, 1) == "U" && getButtonText(row, 2) == "S") {
        return true;
    }

    // Check current column
    if (getButtonText(0, col) == "S" && getButtonText(1, col) == "U" && getButtonText(2, col) == "S") {
        return true;
    }


    // Check primary diagonal (Top-left to bottom-right)
    if (n == 0 || n == 4 || n == 8) {
        if (getButtonText(0, 0) == "S" && getButtonText(1, 1) == "U" && getButtonText(2, 2) == "S") {
            return true;
        }

    }

    // Check secondary diagonal (Top-right to bottom-left)
    if (n == 2 || n == 4 || n == 6) {
        if (getButtonText(0, 2) == "S" && getButtonText(1, 1) == "U" && getButtonText(2, 0) == "S") {
            return true;
        }

    }

    return false;
}




void game2::on_resetButton_1_clicked()
{
    resetAll();
}

void game2::on_pushButton_0_clicked()
{
    handleCheckClick2(0);
}

void game2::on_pushButton_1_clicked()
{
    handleCheckClick2(1);
}

void game2::on_pushButton_2_clicked()
{
    handleCheckClick2(2);
}

void game2::on_pushButton_3_clicked()
{
    handleCheckClick2(3);
}

void game2::on_pushButton_4_clicked()
{
    handleCheckClick2(4);
}

void game2::on_pushButton_5_clicked()
{
    handleCheckClick2(5);
}

void game2::on_pushButton_6_clicked()
{
    handleCheckClick2(6);
}

void game2::on_pushButton_7_clicked()
{
    handleCheckClick2(7);
}

void game2::on_pushButton_8_clicked()
{
    handleCheckClick2(8);
}


