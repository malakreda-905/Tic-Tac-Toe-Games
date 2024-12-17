#include "game1.h"
#include "ui_game1.h"
#include <Qmap>
#include <qtimer.h>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // get only 1 upper case char for symbol input
    ui->player1Symbol->setMaxLength(1);
    ui->player2Symbol->setMaxLength(1);
    connect(ui->player1Symbol, &QLineEdit::textChanged, this, [=](const QString &text) {
        if (!text.isEmpty()) {
            QString upperText = text.left(1).toUpper(); // Convert to uppercase
            ui->player1Symbol->setText(upperText);
        }
    });
    connect(ui->player2Symbol, &QLineEdit::textChanged, this, [=](const QString &text) {
        if (!text.isEmpty()) {
            QString upperText = text.left(1).toUpper(); // Convert to uppercase
            ui->player2Symbol->setText(upperText);
        }
    });
    ///////////////////////////////////////////////
    // disable some items
    ui->resetButton->hide();
    ui->Board1->setEnabled(false);
    ui->Board2->setEnabled(false);
    ui->Board3->setEnabled(false);
    ui->Board4->setEnabled(false);
    ui->Board5->setEnabled(false);
    ui->Board6->setEnabled(false);
    ui->Board7->setEnabled(false);
    ui->Board8->setEnabled(false);
    ui->Board9->setEnabled(false);
    ui->playerTurns->hide();
    ui->gameStarted->hide();
    ui->winB_1->hide();
    ui->winB_2->hide();
    ui->winB_3->hide();
    ui->winB_4->hide();
    ui->winB_5->hide();
    ui->winB_6->hide();
    ui->winB_7->hide();
    ui->winB_8->hide();
    ui->winB_9->hide();
    ui->winBigBoard->hide();
    ///////////////////////////////////////////////
}

QString player1XName, player2XName, player1Symbol, player2Symbol;
bool  currPlayer1 = true, player1Random = false, player2Random = false;
QMap<int,int> n_moves;


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        event->accept(); // Allow the window to close
        on_resetButton_clicked();
    } else {
        event->ignore(); // Ignore the close event
    }
}

void MainWindow::on_playButton_clicked()
{
    n_moves.clear();
    player1XName = ui->player1Name->text();
    player2XName = ui->player2Name->text();
    player1Symbol = ui->player1Symbol->text().toUpper();
    player2Symbol = ui->player2Symbol->text().toUpper();
    // check if names is valid or not
    if (player1XName.size() == 0 ){
        ui->validName1->setText("not valid !");
        if (ui->validName1->isHidden()) ui->validName1->show();
    }
    else if (!ui->validName1->isHidden()){
        ui->validName1->clear();
        ui->validName1->hide();
    }
    if (player2XName.size() == 0){
        ui->validName2->setText("not valid !");
        if (ui->validName2->isHidden()) ui->validName2->show();
    }
    else if (!ui->validName2->isHidden()){
        ui->validName2->clear();
        ui->validName2->hide();
    }
    // set valid symbols
    if (player1Symbol.size() == 0 || player1Symbol == "D"){
        ui->validSymbol1->setText("not valid !");
        if (ui->validSymbol1->isHidden()) ui->validSymbol1->show();
    }
    else if (!ui->validSymbol1->isHidden()){
        ui->validSymbol1->clear();
        ui->validSymbol1->hide();
    }
    if (player2Symbol.size() == 0 || player2Symbol == "D"){
        ui->validSymbol2->setText("not valid !");
        if (ui->validSymbol2->isHidden()) ui->validSymbol2->show();
    }
    else if (player2Symbol == player1Symbol){
        ui->validSymbol2->setText("choose another char please !");
        if (ui->validSymbol2->isHidden()) ui->validSymbol2->show();
    }
    else if (!ui->validSymbol2->isHidden()){
        ui->validSymbol2->clear();
        ui->validSymbol2->hide();
    }
    /////////////////////////////////
    bool allValid = player1XName.size() && player2XName.size() && player1Symbol.size() && player2Symbol.size() && player1Symbol != player2Symbol && player1Symbol != "D" && player2Symbol != "D";
    // check if all valid run the game
    if (allValid){
        ui->player1Name->setReadOnly(true);
        ui->player2Name->setReadOnly(true);
        ui->player1Symbol->setReadOnly(true);
        ui->player2Symbol->setReadOnly(true);
        ui->resetButton->show();
        ui->playButton->setEnabled(false);
        ui->player1Card->hide();
        ui->player2Card->hide();
        ui->Player1->hide();
        ui->Player2->hide();
        ui->Board1->setEnabled(true);
        ui->Board2->setEnabled(true);
        ui->Board3->setEnabled(true);
        ui->Board4->setEnabled(true);
        ui->Board5->setEnabled(true);
        ui->Board6->setEnabled(true);
        ui->Board7->setEnabled(true);
        ui->Board8->setEnabled(true);
        ui->Board9->setEnabled(true);
        ui->checkBox->hide();
        ui->checkBox_2->hide();
        ui->playerTurns->setText("Player " + (currPlayer1 ? player1XName: player2XName) + " Trun !");
        ui->playerTurns->show();
        ui->gameStarted->show();
        ui->gameStarted->setText("Game Started..");
        player1Random = ui->checkBox->isChecked();
        player2Random = ui->checkBox_2->isChecked();
        ui->playButton->hide();
        if (player1Random)
            randomPlayerMove();


    }
}


void MainWindow::resetWinBoardsLable(){
        // Reset winB labels
        for (int i = 1; i <= 9; ++i) {
            QString winBName = QString("winB_%1").arg(i);
            QLabel* winBLabel = findChild<QLabel*>(winBName);
            if (winBLabel) {
                winBLabel->hide();
                winBLabel->setText("");
            }
        }
        ui->winBigBoard->hide();
        ui->winBigBoard->setText("");
    }

void MainWindow::resetPushButtons() {
    for (int i = 1; i <= 9; ++i) {
        for (int j = 0; j <= 8; ++j) {
            QString buttonName = QString("pushButton_%1%2").arg(i).arg(j);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if (button) {
                button->setText("");
                button->setEnabled(true);
            }
        }
    }
}


void MainWindow::on_resetButton_clicked()
{
    player1XName = "";
    player2XName = "";
    player1Symbol = "";
    player2Symbol = "";
    ui->playButton->show();
    ui->player1Name->setText("");
    ui->player2Name->setText("");
    ui->player1Symbol->setText("");
    ui->player2Symbol->setText("");
    ui->player1Name->setReadOnly(false);
    ui->player2Name->setReadOnly(false);
    ui->player1Symbol->setReadOnly(false);
    ui->player2Symbol->setReadOnly(false);
    ui->playButton->setEnabled(true);
    ui->player1Card->show();
    ui->player2Card->show();
    ui->Player1->show();
    ui->Player2->show();
    player1Random = false, player2Random = false, currPlayer1 = true;
    ui->resetButton->hide();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox->show();
    ui->checkBox_2->show();
    ui->playerTurns->hide();
    ui->gameStarted->hide();
    resetWinBoardsLable();
    resetPushButtons();
    n_moves.clear();
    ui->Board1->setEnabled(false);
    ui->Board2->setEnabled(false);
    ui->Board3->setEnabled(false);
    ui->Board4->setEnabled(false);
    ui->Board5->setEnabled(false);
    ui->Board6->setEnabled(false);
    ui->Board7->setEnabled(false);
    ui->Board8->setEnabled(false);
    ui->Board9->setEnabled(false);
}



bool MainWindow::is_win_S_board(QGroupBox *boardn) {
    QList<QPushButton*> buttons = boardn->findChildren<QPushButton*>();

    QString grid[3][3];
    for (QPushButton* button : buttons) {
        QString name = button->objectName();
        int position = name.mid(name.lastIndexOf('_') + 1).toInt();
        int row = (position % 10) / 3;  // Row index
        int col = (position % 10) % 3;  // Column index
        grid[row][col] = button->text();
    }

    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        // Check rows
        if (!grid[i][0].isEmpty() && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return true;
        // Check columns
        if (!grid[0][i].isEmpty() && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
            return true;
    }
    // Check diagonals
    if (!grid[0][0].isEmpty() && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
        return true;
    if (!grid[0][2].isEmpty() && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
        return true;

    return false; // No win condition
}

bool MainWindow::is_win_B_board() {
    QString board[3][3] = {
        { ui->winB_1->text(), ui->winB_2->text(), ui->winB_3->text() },
        { ui->winB_4->text(), ui->winB_5->text(), ui->winB_6->text() },
        { ui->winB_7->text(), ui->winB_8->text(), ui->winB_9->text() }
    };

    // Check rows for a win
    for (int i = 0; i < 3; ++i) {
        if (!board[i][0].isEmpty() && board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != "D") {
            return true;
        }
    }

    // Check columns for a win
    for (int j = 0; j < 3; ++j) {
        if (!board[0][j].isEmpty() && board[0][j] == board[1][j] && board[1][j] == board[2][j]&& board[0][j] != "D") {
            return true;
        }
    }

    // Check main diagonal for a win
    if (!board[0][0].isEmpty() && board[0][0] == board[1][1] && board[1][1] == board[2][2]&& board[0][0] != "D") {
        return true;
    }

    // Check anti-diagonal for a win
    if (!board[0][2].isEmpty() && board[0][2] == board[1][1] && board[1][1] == board[2][0]&& board[0][2] != "D") {
        return true;
    }

    // No win condition
    return false;
}

bool MainWindow::is_draw_B_board(){
    bool allDisabled =
        !ui->Board1->isEnabled() &&
        !ui->Board2->isEnabled() &&
        !ui->Board3->isEnabled() &&
        !ui->Board4->isEnabled() &&
        !ui->Board5->isEnabled() &&
        !ui->Board6->isEnabled() &&
        !ui->Board7->isEnabled() &&
        !ui->Board8->isEnabled() &&
        !ui->Board9->isEnabled();
    return allDisabled && !is_win_B_board();
}
bool MainWindow::is_draw_S_board(int n, QGroupBox *boardn){
    return n_moves[n] == 9 && !is_win_S_board(boardn);
}



void MainWindow::on_checkBox_clicked()
{
    if (player1Random){
        player1Random = false;
        ui->player1Name->setText("");
        ui->player1Symbol->setText("");
    }else{
        player1Random = true;
        ui->player1Name->setText("Random Player 1");
        ui->player1Symbol->setText("X");
    }
}


void MainWindow::on_checkBox_2_clicked()
{
    if (player2Random){
        player2Random = false;
        ui->player2Name->setText("");
        ui->player2Symbol->setText("");
    }else{
        player2Random = true;
        ui->player2Name->setText("Random Player 2");
        ui->player2Symbol->setText("O");
    }
}

void MainWindow::disableAllBoards() {
    ui->Board1->setEnabled(false);
    ui->Board2->setEnabled(false);
    ui->Board3->setEnabled(false);
    ui->Board4->setEnabled(false);
    ui->Board5->setEnabled(false);
    ui->Board6->setEnabled(false);
    ui->Board7->setEnabled(false);
    ui->Board8->setEnabled(false);
    ui->Board9->setEnabled(false);
}


void MainWindow::handleButtonClick(QPushButton *button, QGroupBox *board, QLabel *winLabel, int boardIndex) {
    if (board->isEnabled()) {
        n_moves[boardIndex]++;
        // Set button text and disable it
        button->setText((currPlayer1 ? player1Symbol : player2Symbol));
        button->setEnabled(false);

        // Check win condition for small board
        if (is_win_S_board(board)) {
            winLabel->show();
            winLabel->setText((currPlayer1 ? player1Symbol : player2Symbol));
            winLabel->setStyleSheet(currPlayer1 ?
                                        "QLabel { color : rgb(51, 143, 255); }" :
                                        "QLabel { color : rgb(0, 85, 0); }");
            board->setEnabled(false);
            n_moves[boardIndex] = 9;
        }

        // Check draw condition for small board
        if (is_draw_S_board(boardIndex, board)) {
            winLabel->setText("D");
            winLabel->show();
            winLabel->setStyleSheet("QLabel { color : red; }");
            board->setEnabled(false);
        }
        bool win = is_win_B_board(), draw = is_draw_B_board();
        // Check win/draw condition for the big board
        if (win) {
            ui->winBigBoard->setText(currPlayer1 ? player1Symbol : player2Symbol);
            ui->playerTurns->setText("Player " + (currPlayer1 ? player1XName: player2XName) + " Won !");
            ui->gameStarted->setText("Game Ended.");
            ui->winBigBoard->setStyleSheet("QLabel { color: rgba(255, 255, 255, 128); background: transparent; }");
        } else if (draw) {
            ui->winBigBoard->setText("D");
            ui->gameStarted->setText("Game Over.");
            ui->playerTurns->setText("Draw !");
            ui->winBigBoard->setStyleSheet("QLabel { color: rgba(255, 255, 255, 128); background: transparent; }");

        }else{
            ui->playerTurns->setText("Player " + (currPlayer1 ? player2XName: player1XName) + " Trun !");
            currPlayer1 = !currPlayer1;
        }
        if (win || draw){
            ui->winBigBoard->show();
            disableAllBoards();
            return;
        }
        if (!currPlayer1 && player2Random)     randomPlayerMove();

        if (currPlayer1 && player1Random) randomPlayerMove();

    }
}
void MainWindow::randomPlayerMove() {
    QVector<QPushButton*> availableButtons;


    QVector<QGroupBox*> boards = {ui->Board1, ui->Board2, ui->Board3,
                                   ui->Board4, ui->Board5, ui->Board6,
                                   ui->Board7, ui->Board8, ui->Board9};

    for (int b = 0; b < boards.size(); ++b) {
        if (boards[b]->isEnabled()) {

            for (QPushButton* button : boards[b]->findChildren<QPushButton*>()) {
                if (button->isEnabled()) {
                    availableButtons.append(button);
                }
            }
        }
    }


    if (!availableButtons.isEmpty()) {
        int randomIndex = QRandomGenerator::global()->bounded(availableButtons.size());
        QPushButton* randomButton = availableButtons[randomIndex];


        handleButtonClick(randomButton, getBoardOfButton(randomButton),
                          getWinLabelOfBoard(randomButton), getBoardIndex(randomButton));
    }
}
int MainWindow::getBoardIndex(QPushButton* button) {

    if (getBoardOfButton(button) == ui->Board1) return 1;
    if (getBoardOfButton(button) == ui->Board2) return 2;
    if (getBoardOfButton(button) == ui->Board3) return 3;
    if (getBoardOfButton(button) == ui->Board4) return 4;
    if (getBoardOfButton(button) == ui->Board5) return 5;
    if (getBoardOfButton(button) == ui->Board6) return 6;
    if (getBoardOfButton(button) == ui->Board7) return 7;
    if (getBoardOfButton(button) == ui->Board8) return 8;
    if (getBoardOfButton(button) == ui->Board9) return 9;

    return -1;
}
QLabel* MainWindow::getWinLabelOfBoard(QPushButton* button) {

    if (getBoardOfButton(button) == ui->Board1) return ui->winB_1;
    if (getBoardOfButton(button) == ui->Board2) return ui->winB_2;
    if (getBoardOfButton(button) == ui->Board3) return ui->winB_3;
    if (getBoardOfButton(button) == ui->Board4) return ui->winB_4;
    if (getBoardOfButton(button) == ui->Board5) return ui->winB_5;
    if (getBoardOfButton(button) == ui->Board6) return ui->winB_6;
    if (getBoardOfButton(button) == ui->Board7) return ui->winB_7;
    if (getBoardOfButton(button) == ui->Board8) return ui->winB_8;
    if (getBoardOfButton(button) == ui->Board9) return ui->winB_9;

    return nullptr;
}
QGroupBox* MainWindow::getBoardOfButton(QPushButton* button) {

    QVector<QGroupBox*> boards = {ui->Board1, ui->Board2, ui->Board3,
                                   ui->Board4, ui->Board5, ui->Board6,
                                   ui->Board7, ui->Board8, ui->Board9};

    for (QGroupBox* board : boards) {
        if (board && board->findChildren<QPushButton*>().contains(button)) {
            return board;
        }
    }
    return nullptr;
}


// Board1
// Board1
void MainWindow::on_pushButton_10_clicked() {
    handleButtonClick(ui->pushButton_10, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_11_clicked() {
    handleButtonClick(ui->pushButton_11, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_12_clicked() {
    handleButtonClick(ui->pushButton_12, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_13_clicked() {
    handleButtonClick(ui->pushButton_13, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_14_clicked() {
    handleButtonClick(ui->pushButton_14, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_15_clicked() {
    handleButtonClick(ui->pushButton_15, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_16_clicked() {
    handleButtonClick(ui->pushButton_16, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_17_clicked() {
    handleButtonClick(ui->pushButton_17, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_18_clicked() {
    handleButtonClick(ui->pushButton_18, ui->Board1, ui->winB_1, 1);
}

void MainWindow::on_pushButton_20_clicked() {
    handleButtonClick(ui->pushButton_20, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_21_clicked() {
    handleButtonClick(ui->pushButton_21, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_22_clicked() {
    handleButtonClick(ui->pushButton_22, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_23_clicked() {
    handleButtonClick(ui->pushButton_23, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_24_clicked() {
    handleButtonClick(ui->pushButton_24, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_25_clicked() {
    handleButtonClick(ui->pushButton_25, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_26_clicked() {
    handleButtonClick(ui->pushButton_26, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_27_clicked() {
    handleButtonClick(ui->pushButton_27, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_28_clicked() {
    handleButtonClick(ui->pushButton_28, ui->Board2, ui->winB_2, 2);
}

void MainWindow::on_pushButton_30_clicked() {
    handleButtonClick(ui->pushButton_30, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_31_clicked() {
    handleButtonClick(ui->pushButton_31, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_32_clicked() {
    handleButtonClick(ui->pushButton_32, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_33_clicked() {
    handleButtonClick(ui->pushButton_33, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_34_clicked() {
    handleButtonClick(ui->pushButton_34, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_35_clicked() {
    handleButtonClick(ui->pushButton_35, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_36_clicked() {
    handleButtonClick(ui->pushButton_36, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_37_clicked() {
    handleButtonClick(ui->pushButton_37, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_38_clicked() {
    handleButtonClick(ui->pushButton_38, ui->Board3, ui->winB_3, 3);
}

void MainWindow::on_pushButton_40_clicked() {
    handleButtonClick(ui->pushButton_40, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_41_clicked() {
    handleButtonClick(ui->pushButton_41, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_42_clicked() {
    handleButtonClick(ui->pushButton_42, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_43_clicked() {
    handleButtonClick(ui->pushButton_43, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_44_clicked() {
    handleButtonClick(ui->pushButton_44, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_45_clicked() {
    handleButtonClick(ui->pushButton_45, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_46_clicked() {
    handleButtonClick(ui->pushButton_46, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_47_clicked() {
    handleButtonClick(ui->pushButton_47, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_48_clicked() {
    handleButtonClick(ui->pushButton_48, ui->Board4, ui->winB_4, 4);
}

void MainWindow::on_pushButton_50_clicked() {
    handleButtonClick(ui->pushButton_50, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_51_clicked() {
    handleButtonClick(ui->pushButton_51, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_52_clicked() {
    handleButtonClick(ui->pushButton_52, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_53_clicked() {
    handleButtonClick(ui->pushButton_53, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_54_clicked() {
    handleButtonClick(ui->pushButton_54, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_55_clicked() {
    handleButtonClick(ui->pushButton_55, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_56_clicked() {
    handleButtonClick(ui->pushButton_56, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_57_clicked() {
    handleButtonClick(ui->pushButton_57, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_58_clicked() {
    handleButtonClick(ui->pushButton_58, ui->Board5, ui->winB_5, 5);
}

void MainWindow::on_pushButton_60_clicked() {
    handleButtonClick(ui->pushButton_60, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_61_clicked() {
    handleButtonClick(ui->pushButton_61, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_62_clicked() {
    handleButtonClick(ui->pushButton_62, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_63_clicked() {
    handleButtonClick(ui->pushButton_63, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_64_clicked() {
    handleButtonClick(ui->pushButton_64, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_65_clicked() {
    handleButtonClick(ui->pushButton_65, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_66_clicked() {
    handleButtonClick(ui->pushButton_66, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_67_clicked() {
    handleButtonClick(ui->pushButton_67, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_68_clicked() {
    handleButtonClick(ui->pushButton_68, ui->Board6, ui->winB_6, 6);
}

void MainWindow::on_pushButton_70_clicked() {
    handleButtonClick(ui->pushButton_70, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_71_clicked() {
    handleButtonClick(ui->pushButton_71, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_72_clicked() {
    handleButtonClick(ui->pushButton_72, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_73_clicked() {
    handleButtonClick(ui->pushButton_73, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_74_clicked() {
    handleButtonClick(ui->pushButton_74, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_75_clicked() {
    handleButtonClick(ui->pushButton_75, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_76_clicked() {
    handleButtonClick(ui->pushButton_76, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_77_clicked() {
    handleButtonClick(ui->pushButton_77, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_78_clicked() {
    handleButtonClick(ui->pushButton_78, ui->Board7, ui->winB_7, 7);
}

void MainWindow::on_pushButton_80_clicked() {
    handleButtonClick(ui->pushButton_80, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_81_clicked() {
    handleButtonClick(ui->pushButton_81, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_82_clicked() {
    handleButtonClick(ui->pushButton_82, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_83_clicked() {
    handleButtonClick(ui->pushButton_83, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_84_clicked() {
    handleButtonClick(ui->pushButton_84, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_85_clicked() {
    handleButtonClick(ui->pushButton_85, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_86_clicked() {
    handleButtonClick(ui->pushButton_86, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_87_clicked() {
    handleButtonClick(ui->pushButton_87, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_88_clicked() {
    handleButtonClick(ui->pushButton_88, ui->Board8, ui->winB_8, 8);
}

void MainWindow::on_pushButton_90_clicked() {
    handleButtonClick(ui->pushButton_90, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_91_clicked() {
    handleButtonClick(ui->pushButton_91, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_92_clicked() {
    handleButtonClick(ui->pushButton_92, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_93_clicked() {
    handleButtonClick(ui->pushButton_93, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_94_clicked() {
    handleButtonClick(ui->pushButton_94, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_95_clicked() {
    handleButtonClick(ui->pushButton_95, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_96_clicked() {
    handleButtonClick(ui->pushButton_96, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_97_clicked() {
    handleButtonClick(ui->pushButton_97, ui->Board9, ui->winB_9, 9);
}

void MainWindow::on_pushButton_98_clicked() {
    handleButtonClick(ui->pushButton_98, ui->Board9, ui->winB_9, 9);
}



