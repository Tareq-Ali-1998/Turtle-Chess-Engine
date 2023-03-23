#include <bits/stdc++.h>

using namespace std;

// From here I can control every thing \\

const string ENGINE_NAME = "Turtle";
const int NUMBER_OF_MOVES_TO_CALCULATE = 6;
const long long MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES = 1000000000;
pair<pair<int, int>, pair<int, int>> lastMove = {{-1, -1}, {-1, -1}};

// ....................................... \\





// And here are the global variables...... \\

long long numberOfCalculatedStatesNow = 0;
bool theEngineWillWinForSure = 0;
char whatToReturn = '#';

// ....................................... \\





class Piece {

    public:

        // Piece class attributes..
        int id;
        int points;
        int color;
        int row;
        int column;
        int movesTillNow;

        // Default constructor..
        Piece() {

            this -> id = 0;
            this -> points = 0;
            this -> color = -1;
            this -> row = 0;
            this -> column = 0;
            this -> movesTillNow = 0;

        }

        // Parameterized constructor..
        Piece(int id, int points, int color,
               int row, int column, int movesTillNow) {

            this -> id = id;
            this -> points = points;
            this -> color = color;
            this -> row = row;
            this -> column = column;
            this -> movesTillNow = movesTillNow;

        }

        // Assignment operator overloading..
        operator = (const Piece assignmentRightSide) {

            this -> id = assignmentRightSide.id;
            this -> points = assignmentRightSide.points;
            this -> color = assignmentRightSide.color;
            this -> row = assignmentRightSide.row;
            this -> column = assignmentRightSide.column;
            this -> movesTillNow = assignmentRightSide.movesTillNow;

        }

        // Equality operator overloading..
        bool operator == (const Piece equalityRightSide) {

            return ((bool)((this -> id == equalityRightSide.id) &&
                    (this -> points == equalityRightSide.points) &&
                     (this -> color == equalityRightSide.color) &&
                      (this -> row == equalityRightSide.row) &&
                       (this -> column == equalityRightSide.column) &&
                        (this -> movesTillNow == equalityRightSide.movesTillNow)));

        }

};


void PrintTheBoard(const vector<vector<Piece>>& board) {

    cout << "\n    The board now:\n\n";
    for (int row = 1; row < 9; row++) {
        cout << "    ";
        for (int col = 1; col < 9; col++) {
            if (board[row][col].color == 0) {
                cout << "W";
            }
            else if (board[row][col].color == 1) {
                cout << "B";
            }
            else {
                cout << 0;
            }
        }
        cout << "\n";
    }
    cout << "\n";

    return;

}


void Initialization(vector<vector<Piece>>& board,
                     vector<Piece>& whitePieces,
                      vector<Piece>& blackPieces) {

    // Initializing black pieces..
    board[1][1] = Piece(4, 50, 1, 1, 1, 0);
    board[1][2] = Piece(2, 29, 1, 1, 2, 0);
    board[1][3] = Piece(3, 30, 1, 1, 3, 0);
    board[1][4] = Piece(5, 90, 1, 1, 4, 0);
    board[1][5] = Piece(6, 1000000, 1, 1, 5, 0);
    board[1][6] = Piece(3, 30, 1, 1, 6, 0);
    board[1][7] = Piece(2, 29, 1, 1, 7, 0);
    board[1][8] = Piece(4, 50, 1, 1, 8, 0);

    for (int column = 1; column < 9; column++) {
        board[2][column] = Piece(1, 10, 1, 2, column, 0);
        blackPieces.push_back(board[1][column]);
        blackPieces.push_back(board[2][column]);
    }


    // Initializing white pieces..
    board[8][1] = Piece(4, 50, 0, 8, 1, 0);
    board[8][2] = Piece(2, 29, 0, 8, 2, 0);
    board[8][3] = Piece(3, 30, 0, 8, 3, 0);
    board[8][4] = Piece(5, 90, 0, 8, 4, 0);
    board[8][5] = Piece(6, 1000000, 0, 8, 5, 0);
    board[8][6] = Piece(3, 30, 0, 8, 6, 0);
    board[8][7] = Piece(2, 29, 0, 8, 7, 0);
    board[8][8] = Piece(4, 50, 0, 8, 8, 0);

    for (int column = 1; column < 9; column++) {
        board[7][column] = Piece(1, 10, 0, 7, column, 0);
        whitePieces.push_back(board[7][column]);
        whitePieces.push_back(board[8][column]);
    }

    return;

}


void SpecialInitialization(vector<vector<Piece>>& board,
                            vector<Piece>& whitePieces,
                             vector<Piece>& blackPieces) {



    // Initializing white pieces..
    board[2][4] = Piece(2, 29, 0, 2, 4, 10);
    board[3][8] = Piece(5, 90, 0, 3, 8, 10);
    board[4][4] = Piece(1, 10, 0, 4, 4, 10);
    board[5][4] = Piece(3, 30, 0, 5, 4, 10);
    board[5][5] = Piece(4, 50, 0, 5, 5, 10);
    board[7][3] = Piece(3, 30, 0, 7, 3, 10);
    board[8][3] = Piece(6, 1000000, 0, 8, 3, 10);


    // Initializing black pieces..
    board[2][6] = Piece(5, 90, 1, 2, 6, 10);
    board[3][5] = Piece(2, 29, 1, 3, 5, 10);
    board[4][3] = Piece(1, 10, 1, 4, 3, 10);
    board[4][6] = Piece(6, 1000000, 1, 4, 6, 10);
    board[4][7] = Piece(4, 50, 1, 4, 7, 10);
    board[5][3] = Piece(4, 50, 1, 5, 3, 10);
    board[5][7] = Piece(1, 10, 1, 5, 7, 10);
    board[6][3] = Piece(1, 10, 1, 6, 3, 10);
    board[6][7] = Piece(3, 30, 1, 6, 7, 10);
    board[7][8] = Piece(2, 29, 1, 7, 8, 10);


    // Filling the vectors..
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            if ((board[i][j].id) && (!board[i][j].color)) {
                whitePieces.push_back(board[i][j]);
            }
            else if (board[i][j].id) {
                blackPieces.push_back(board[i][j]);
            }
        }
    }

    return;

}


bool SayHello() {

    cout << "\nHello, I am " << ENGINE_NAME << " chess engine, and "
            "I am better than Stockfish chess engine, so\n"
            "let's play our game ;) .\n"
            "Yes I am talking to you my opponent, if you want to choose "
            "White press 1, otherwise press 0:\n";

    bool choice;
    cin >> choice;
    if (choice) {
        cout << "\n" << ENGINE_NAME << " engine is Black, and you are White, let's"
                " move on ;) :\n\n\n";
    }
    else {
        cout << "\n" << ENGINE_NAME << " engine is White, you are Black, let's"
                " move on ;) :\n\n\n";
    }

    return choice;

}


int GetMyScore(vector<Piece>& whitePieces,
                vector<Piece>& blackPieces,
                 const bool& myColor) {

    int myScore = 0;
    if (!myColor) {
        for (Piece currentPiece : whitePieces) {
            myScore += currentPiece.points;
        }
    }
    else {
        for (Piece currentPiece : blackPieces) {
            myScore += currentPiece.points;
        }
    }

    return myScore;

}


int GetOpponentScore(vector<Piece>& whitePieces,
                      vector<Piece>& blackPieces,
                       const bool& myColor) {

    int opponentScore = 0;
    if (!myColor) {
        for (Piece currentPiece : blackPieces) {
            opponentScore += currentPiece.points;
        }
    }
    else {
        for (Piece currentPiece : whitePieces) {
            opponentScore += currentPiece.points;
        }
    }

    return opponentScore;

}


bool Valid(const pair<int, int>& from, const pair<int, int>& to,
            const vector<vector<Piece>>& board) {

    return (bool)((to.first > 0) && (to.first < 9) &&
                  (to.second > 0) && (to.second < 9) &&
                   (board[from.first][from.second].color !=
                    board[to.first][to.second].color));

}


vector<pair<pair<int, int>, pair<int, int>>> GetMoves(
                                          const Piece& currentPiece,
                                           vector<vector<Piece>>& board);


bool IsThisCellSaveForWhite(vector<vector<Piece>>& board,
                             pair<int, int> cell) {

    Piece realPiece = board[cell.first][cell.second];

    // Try a knight..
    board[cell.first][cell.second] = Piece(2, 29, 0, cell.first, cell.second, 2);
    auto moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if (board[currentMove.second.first][currentMove.second.second].id == 2) {
             board[cell.first][cell.second] = realPiece;
             return 0;
         }

    }


    // Try a pawn..
    board[cell.first][cell.second] = Piece(1, 10, 0, cell.first, cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if (board[currentMove.second.first][currentMove.second.second].id == 1) {
             board[cell.first][cell.second] = realPiece;
             return 0;
         }

    }


    // Try a rock..
    board[cell.first][cell.second] = Piece(4, 50, 0, cell.first, cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if ((board[currentMove.second.first][currentMove.second.second].id == 4) ||
             (board[currentMove.second.first][currentMove.second.second].id == 5)) {

             board[cell.first][cell.second] = realPiece;
             return 0;

         }

    }

    // Try a bishop..
    board[cell.first][cell.second] = Piece(3, 30, 0, cell.first, cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if ((board[currentMove.second.first][currentMove.second.second].id == 3) ||
             (board[currentMove.second.first][currentMove.second.second].id == 5)) {

             board[cell.first][cell.second] = realPiece;
             return 0;

         }

    }

    // Try a king..
    board[cell.first][cell.second] = Piece(6, 1000000, 0, cell.first,
                                            cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if (board[currentMove.second.first][currentMove.second.second].id == 6) {
             board[cell.first][cell.second] = realPiece;
             return 0;
         }

    }

    board[cell.first][cell.second] = realPiece;
    return 1;

}


bool IsThisCellSaveForBlack(vector<vector<Piece>>& board,
                             pair<int, int> cell) {

    Piece realPiece = board[cell.first][cell.second];

    // Try a knight..
    board[cell.first][cell.second] = Piece(2, 29, 1, cell.first, cell.second, 2);
    auto moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if (board[currentMove.second.first][currentMove.second.second].id == 2) {
             board[cell.first][cell.second] = realPiece;
             return 0;
        }

    }

    // Try a pawn..
    board[cell.first][cell.second] = Piece(1, 10, 1, cell.first, cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if (board[currentMove.second.first][currentMove.second.second].id == 1) {
             board[cell.first][cell.second] = realPiece;
             return 0;
        }

    }


    // Try a rook..
    board[cell.first][cell.second] = Piece(4, 50, 1, cell.first, cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if ((board[currentMove.second.first][currentMove.second.second].id == 4) ||
             (board[currentMove.second.first][currentMove.second.second].id == 5)) {

             board[cell.first][cell.second] = realPiece;
             return 0;

        }

    }

    // Try a bishop..
    board[cell.first][cell.second] = Piece(3, 30, 1, cell.first, cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if ((board[currentMove.second.first][currentMove.second.second].id == 3) ||
             (board[currentMove.second.first][currentMove.second.second].id == 5)) {

             board[cell.first][cell.second] = realPiece;
             return 0;

        }

    }

    // Try a king..
    board[cell.first][cell.second] = Piece(6, 1000000, 1, cell.first,
                                            cell.second, 2);
    moves = GetMoves(board[cell.first][cell.second], board);
    for (auto currentMove : moves) {

         if (board[currentMove.second.first][currentMove.second.second].id == 6) {
             board[cell.first][cell.second] = realPiece;
             return 0;
        }

    }

    board[cell.first][cell.second] = realPiece;
    return 1;

}


void MakeChanges(const pair<pair<int, int>, pair<int, int>>& currentMove,
                  vector<vector<Piece>>& board, vector<Piece>& whitePieces,
                   vector<Piece>& blackPieces, const bool& myColor,
                    int& myScore, int& opponentScore) {

    // Changing the scores..
    if ((board[currentMove.second.first][currentMove.second.second].id)
        && (board[currentMove.second.first]
            [currentMove.second.second].color == myColor)) {

        myScore -= board[currentMove.second.first]
                         [currentMove.second.second].points;

    }
    else if (board[currentMove.second.first][currentMove.second.second].id) {

        opponentScore -= board[currentMove.second.first]
                               [currentMove.second.second].points;

    }

    // Changing the board..
    board[currentMove.second.first][currentMove.second.second] =
                   board[currentMove.first.first][currentMove.first.second];

    board[currentMove.second.first][currentMove.second.second].row =
                                                    currentMove.second.first;
    board[currentMove.second.first][currentMove.second.second].column =
                                                    currentMove.second.second;
    board[currentMove.second.first][currentMove.second.second].movesTillNow++;

    board[currentMove.first.first][currentMove.first.second] = Piece();


    // Changing the vectors..
    if (!board[currentMove.second.first][currentMove.second.second].color) {
        whitePieces.push_back(board[currentMove.second.first]
                                    [currentMove.second.second]);
    }
    else {
        blackPieces.push_back(board[currentMove.second.first]
                                    [currentMove.second.second]);
    }

    return;

}


void ReturnEveryThingAsItWas(const pair<pair<int, int>,
                              pair<int, int>>& currentMove,
                               const Piece& sourcePiece,
                                const Piece& destinationPiece,
                                 vector<vector<Piece>>& board,
                                  vector<Piece>& whitePieces,
                                   vector<Piece>& blackPieces,
                                    const bool& myColor,
                                     int& myScore, int& opponentScore) {

    // Returning the scores..
    if ((destinationPiece.id) && (destinationPiece.color == myColor)) {
        myScore += destinationPiece.points;
    }
    else if (destinationPiece.id) {
        opponentScore += destinationPiece.points;
    }

    // Returning the vectors..
    if (sourcePiece.color == 0) {
        whitePieces.pop_back();
    }
    else if (sourcePiece.color == 1){
        blackPieces.pop_back();
    }

    // Returning the board..
    board[currentMove.first.first][currentMove.first.second] = sourcePiece;
    board[currentMove.second.first][currentMove.second.second] = destinationPiece;

    return;

}


void HandleQueenReturningMoveChanges(const pair<pair<int, int>,
                            pair<int, int>>& currentMove,
                             vector<vector<Piece>>& board,
                              vector<Piece>& whitePieces,
                               vector<Piece>& blackPieces,
                                const bool& myColor,
                                 int& myScore, int& opponentScore) {

    // Changing the scores..
    if (board[currentMove.second.first]
        [currentMove.second.second].color == myColor) {

        myScore -=
            board[currentMove.second.first][currentMove.second.second].points;

    }
    else if (board[currentMove.second.first]
                   [currentMove.second.second].color == !myColor) {

        opponentScore -=
            board[currentMove.second.first][currentMove.second.second].points;

    }

    if (board[currentMove.first.first]
        [currentMove.first.second].color == myColor) {

        myScore -= 10;
        myScore += 90;

    }
    else {

        opponentScore -= 10;
        opponentScore += 90;

    }

    // Changing the board, the order of the statements is too important..
    board[currentMove.second.first]
          [currentMove.second.second] = Piece(5, 90, board[currentMove.first.first]
                                              [currentMove.first.second].color,
                                               currentMove.second.first,
                                                currentMove.second.second, 1000000);

    board[currentMove.first.first][currentMove.first.second] = Piece();


    // Changing the vectors..
    if (!board[currentMove.second.first][currentMove.second.second].color) {
        whitePieces.push_back(board[currentMove.second.first]
                                    [currentMove.second.second]);
    }
    else {

        blackPieces.push_back(board[currentMove.second.first]
                                    [currentMove.second.second]);

    }


}


void ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                            const pair<pair<int, int>,
                             pair<int, int>>& currentMove,
                              const Piece& sourcePiece,
                               const Piece& destinationPiece,
                                vector<vector<Piece>>& board,
                                 vector<Piece>& whitePieces,
                                  vector<Piece>& blackPieces,
                                   const bool& myColor,
                                    int& myScore, int& opponentScore) {

    // Returning the scores..
    if ((destinationPiece.id) && (destinationPiece.color == myColor)) {
        myScore += destinationPiece.points;
    }
    else if (destinationPiece.id) {
        opponentScore += destinationPiece.points;
    }

    if (sourcePiece.color == myColor) {

        myScore += 10;
        myScore -= 90;

    }
    else {

        opponentScore += 10;
        opponentScore -= 90;

    }

    // Returning the vectors..
    if (!sourcePiece.color) {
        whitePieces.pop_back();
    }
    else {
        blackPieces.pop_back();
    }

    // Returning the board..
    board[currentMove.first.first][currentMove.first.second] = sourcePiece;
    board[currentMove.second.first][currentMove.second.second] = destinationPiece;


}


void HandleKnightReturningMoveChanges(const pair<pair<int, int>,
                            pair<int, int>>& currentMove,
                             vector<vector<Piece>>& board,
                              vector<Piece>& whitePieces,
                               vector<Piece>& blackPieces,
                                const bool& myColor,
                                 int& myScore, int& opponentScore) {

    // Changing the scores..
    if (board[currentMove.second.first]
        [currentMove.second.second].color == myColor) {

        myScore -=
            board[currentMove.second.first][currentMove.second.second].points;

    }
    else if (board[currentMove.second.first]
                   [currentMove.second.second].color == !myColor) {

        opponentScore -=
            board[currentMove.second.first][currentMove.second.second].points;

    }

    if (board[currentMove.first.first]
        [currentMove.first.second].color == myColor) {

        myScore -= 10;
        myScore += 29;

    }
    else {

        opponentScore -= 10;
        opponentScore += 29;

    }

    // Changing the board, the order of the statements is too important..
    board[currentMove.second.first]
          [currentMove.second.second] = Piece(2, 29, board[currentMove.first.first]
                                              [currentMove.first.second].color,
                                               currentMove.second.first,
                                                currentMove.second.second, 1000000);

    board[currentMove.first.first][currentMove.first.second] = Piece();


    // Changing the vectors..
    if (!board[currentMove.second.first][currentMove.second.second].color) {
        whitePieces.push_back(board[currentMove.second.first]
                                    [currentMove.second.second]);
    }
    else {

        blackPieces.push_back(board[currentMove.second.first]
                                    [currentMove.second.second]);

    }


}


void ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                            const pair<pair<int, int>,
                             pair<int, int>>& currentMove,
                              const Piece& sourcePiece,
                               const Piece& destinationPiece,
                                vector<vector<Piece>>& board,
                                 vector<Piece>& whitePieces,
                                  vector<Piece>& blackPieces,
                                   const bool& myColor,
                                    int& myScore, int& opponentScore) {

    // Returning the scores..
    if ((destinationPiece.id) && (destinationPiece.color == myColor)) {
        myScore += destinationPiece.points;
    }
    else if (destinationPiece.id) {
        opponentScore += destinationPiece.points;
    }

    if (sourcePiece.color == myColor) {

        myScore += 10;
        myScore -= 29;

    }
    else {

        opponentScore += 10;
        opponentScore -= 29;

    }

    // Returning the vectors..
    if (!sourcePiece.color) {
        whitePieces.pop_back();
    }
    else {
        blackPieces.pop_back();
    }

    // Returning the board..
    board[currentMove.first.first][currentMove.first.second] = sourcePiece;
    board[currentMove.second.first][currentMove.second.second] = destinationPiece;


}


void ChangeEverThingAfterCastling(const pair<pair<int, int>,
                                   pair<int, int>>& currentMove,
                                    vector<vector<Piece>>& board,
                                     vector<Piece>& whitePieces,
                                      vector<Piece>& blackPieces,
                                       Piece& sourcePiece,
                                        Piece& destinationPiece) {

    sourcePiece.movesTillNow++;
    destinationPiece.movesTillNow++;

    if (currentMove.first.first == 1) {

        if (currentMove.first.second == 1) {

            board[1][4] = sourcePiece;
            board[1][3] = destinationPiece;
            board[1][4].row = 1;
            board[1][4].column = 4;
            board[1][3].row = 1;
            board[1][3].column = 3;
            board[1][4].movesTillNow = 1;
            board[1][3].movesTillNow = 1;
            blackPieces.push_back(board[1][4]);
            blackPieces.push_back(board[1][3]);

        }
        else {

            board[1][6] = sourcePiece;
            board[1][7] = destinationPiece;
            board[1][6].row = 1;
            board[1][6].column = 6;
            board[1][7].row = 1;
            board[1][7].column = 7;
            board[1][6].movesTillNow = 1;
            board[1][7].movesTillNow = 1;
            blackPieces.push_back(board[1][6]);
            blackPieces.push_back(board[1][7]);

        }

    }
    else {

        if (currentMove.first.second == 1) {

            board[8][4] = sourcePiece;
            board[8][3] = destinationPiece;
            board[8][4].row = 8;
            board[8][4].column = 4;
            board[8][3].row = 8;
            board[8][3].column = 3;
            board[8][4].movesTillNow = 1;
            board[8][3].movesTillNow = 1;
            whitePieces.push_back(board[8][4]);
            whitePieces.push_back(board[8][3]);

        }
        else {

            board[8][6] = sourcePiece;
            board[8][7] = destinationPiece;
            board[8][6].row = 8;
            board[8][6].column = 6;
            board[8][7].row = 8;
            board[8][7].column = 7;
            board[8][6].movesTillNow = 1;
            board[8][7].movesTillNow = 1;
            whitePieces.push_back(board[8][6]);
            whitePieces.push_back(board[8][7]);

        }

    }

    board[currentMove.first.first][currentMove.first.second] = Piece();
    board[currentMove.second.first][currentMove.second.second] = Piece();

    return;

}


void ReturnEverThingBeforeCastling(const pair<pair<int, int>,
                                    pair<int, int>>& currentMove,
                                     vector<vector<Piece>>& board,
                                      vector<Piece>& whitePieces,
                                       vector<Piece>& blackPieces,
                                        Piece& sourcePiece,
                                         Piece& destinationPiece) {

    sourcePiece.movesTillNow--;
    destinationPiece.movesTillNow--;

    if (currentMove.first.first == 1) {

        if (currentMove.first.second == 1) {

            board[1][4] = Piece();
            board[1][3] = Piece();
            blackPieces.pop_back();
            blackPieces.pop_back();

        }
        else {

            board[1][6] = Piece();
            board[1][7] = Piece();
            blackPieces.pop_back();
            blackPieces.pop_back();

        }

    }
    else {

        if (currentMove.first.second == 1) {

            board[8][4] = Piece();
            board[8][3] = Piece();
            whitePieces.pop_back();
            whitePieces.pop_back();

        }
        else {

            board[8][6] = Piece();
            board[8][7] = Piece();
            whitePieces.pop_back();
            whitePieces.pop_back();

        }

    }

    board[currentMove.first.first][currentMove.first.second] = sourcePiece;
    board[currentMove.second.first][currentMove.second.second] = destinationPiece;

    return;

}


void ChangeEveryThingAfterInPassingMove(const pair<pair<int, int>,
                                         pair<int, int>>& currentMove,
                                          vector<vector<Piece>>& board,
                                           vector<Piece>& whitePieces,
                                            vector<Piece>& blackPieces,
                                             const bool& myColor,
                                              int& myScore, int& opponentScore) {

    if (!board[currentMove.first.first][currentMove.first.second].color) {

        board[currentMove.second.first - 1][currentMove.second.second] =
         board[currentMove.first.first][currentMove.first.second];

        board[currentMove.second.first - 1]
              [currentMove.second.second].movesTillNow++;

        whitePieces.push_back(board[currentMove.second.first - 1]
                                    [currentMove.second.second]);

        if (!myColor) {
            opponentScore -= 10;
        }
        else {
            myScore -= 10;
        }

    }
    else {
        board[currentMove.second.first + 1]
              [currentMove.second.second] =
               board[currentMove.first.first][currentMove.first.second];

        board[currentMove.second.first + 1]
              [currentMove.second.second].movesTillNow++;

        blackPieces.push_back(board[currentMove.second.first + 1]
                                    [currentMove.second.second]);

        if (!myColor) {
            myScore -= 10;
        }
        else {
            opponentScore -= 10;
        }

    }

    board[currentMove.first.first][currentMove.first.second] = Piece();
    board[currentMove.second.first][currentMove.second.second] = Piece();

    return;

}


void ReturnEveryThingBeforeInPassingMove(const pair<pair<int, int>,
                                          pair<int, int>>& currentMove,
                                           vector<vector<Piece>>& board,
                                            vector<Piece>& whitePieces,
                                             vector<Piece>& blackPieces,
                                              const Piece& sourcePiece,
                                               const Piece& destinationPiece,
                                                const bool& myColor,
                                                 int& myScore,
                                                  int& opponentScore) {

    if (!sourcePiece.color) {
        board[currentMove.second.first - 1][currentMove.second.second] = Piece();
        whitePieces.pop_back();
        if (!myColor) {
            opponentScore += 10;
        }
        else {
            myScore += 10;
        }
    }
    else {
        board[currentMove.second.first + 1][currentMove.second.second] = Piece();
        blackPieces.pop_back();
        if (!myColor) {
            myScore += 10;
        }
        else {
            opponentScore += 10;
        }
    }

    board[currentMove.first.first][currentMove.first.second] = sourcePiece;
    board[currentMove.second.first][currentMove.second.second] = destinationPiece;

    return;

}


int Magic(vector<vector<Piece>>& board, vector<Piece>& whitePieces,
           vector<Piece>& blackPieces, const bool& myColor, int& myScore,
            int& opponentScore, int myTurn, int movesNumber, int alpha, int beta,
             pair<pair<int, int>, pair<int, int>> previousMove) {

    if (numberOfCalculatedStatesNow >
                     MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES) {

        /*
          Just ending the process and I will not play it ever, so
          it is very normal to return 0.
        */
        return 0;

    }


    if (!movesNumber) {
        numberOfCalculatedStatesNow++;
        if (myTurn) {
            alpha = max(alpha, myScore - opponentScore);
            if (beta <= alpha) {
                return INT_MAX;
            }
        }
        else {
            beta = min(beta, myScore - opponentScore);
            if (beta <= alpha) {
                return INT_MIN;
            }
        }
        return (myScore - opponentScore);
    }

    if (((int)(abs(myScore - opponentScore))) > 10000) {
        // This means the death of the king..
        numberOfCalculatedStatesNow++;
        if (myTurn) {
            alpha = max(alpha, myScore - opponentScore);
            if (beta <= alpha) {
                return INT_MAX;
            }
        }
        else {
            beta = min(beta, myScore - opponentScore);
            if (beta <= alpha) {
                return INT_MIN;
            }
        }
        return (myScore - opponentScore);
    }

    if (myTurn) { // This means if it is engine's turn..

        int result = INT_MIN;

        if (!myColor) {

            for (int i = 0; i < (int)whitePieces.size(); i++) {
                Piece currentPiece = whitePieces[i];

                if (!(board[currentPiece.row][currentPiece.column]
                    == currentPiece)) {
                    continue;
                }

                auto moves = GetMoves(currentPiece, board);
                for (auto currentMove : moves) {

                    Piece sourcePiece = board[currentMove.first.first]
                                          [currentMove.first.second];
                    Piece destinationPiece = board[currentMove.second.first]
                                                   [currentMove.second.second];

                    // I have to handle castling too..

                    // This is the returning case for white..
                    if ((sourcePiece.id == 1) && (currentMove.second.first == 1)) {

                    // Try returning the Queen..
                    HandleQueenReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    // Try returning the Knight..
                    HandleKnightReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);


                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    continue;

                }

                // This is the castling..
                if (sourcePiece.color == destinationPiece.color) {

                    ChangeEverThingAfterCastling(currentMove, board,
                                                  whitePieces, blackPieces,
                                                   sourcePiece, destinationPiece);


                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                      alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEverThingBeforeCastling(currentMove, board,
                                                   whitePieces, blackPieces,
                                                    sourcePiece, destinationPiece);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    continue;

                }

                // This is the pawn in passing special move..
                if ((sourcePiece.id == 1) &&
                     (destinationPiece.id == 1) &&
                      (sourcePiece.row == destinationPiece.row) &&
                       (previousMove.second == currentMove.second)) {


                    ChangeEveryThingAfterInPassingMove(currentMove, board,
                                                        whitePieces, blackPieces,
                                                         myColor, myScore,
                                                          opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEveryThingBeforeInPassingMove(currentMove, board,
                                                         whitePieces, blackPieces,
                                                          sourcePiece,
                                                           destinationPiece,
                                                            myColor, myScore,
                                                             opponentScore);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    continue;

                }
                else if ((sourcePiece.id == 1) &&
                          (destinationPiece.id == 1) &&
                           (sourcePiece.row == destinationPiece.row)) {

                      continue;

                }

                MakeChanges(currentMove, board, whitePieces, blackPieces,
                             myColor, myScore, opponentScore);


                int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                result = max(result, currentDifference);

                ReturnEveryThingAsItWas(currentMove, sourcePiece,
                                         destinationPiece, board, whitePieces,
                                          blackPieces, myColor, myScore,
                                           opponentScore);


                alpha = max(alpha, currentDifference);
                if (beta <= alpha) {
                    numberOfCalculatedStatesNow++;
                    return INT_MAX;
                }

                }

            }

        }
        else {

            for (int i = 0; i < (int)blackPieces.size(); i++) {
                Piece currentPiece = blackPieces[i];

                if (!(board[currentPiece.row][currentPiece.column]
                    == currentPiece)) {
                    continue;
                }

                auto moves = GetMoves(currentPiece, board);
                for (auto currentMove : moves) {

                    Piece sourcePiece = board[currentMove.first.first]
                                          [currentMove.first.second];
                    Piece destinationPiece = board[currentMove.second.first]
                                                   [currentMove.second.second];

                    // I have to handle castling too..

                    // This is the returning case for black..
                    if ((sourcePiece.id == 1) && (currentMove.second.first == 8)) {

                    // Try returning the Queen..
                    HandleQueenReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    // Try returning the Knight..
                    HandleKnightReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    continue;

                }

                // This is the castling..
                if (sourcePiece.color == destinationPiece.color) {

                    ChangeEverThingAfterCastling(currentMove, board,
                                                  whitePieces, blackPieces,
                                                   sourcePiece, destinationPiece);


                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);


                    result = max(result, currentDifference);

                    ReturnEverThingBeforeCastling(currentMove, board,
                                                   whitePieces, blackPieces,
                                                    sourcePiece, destinationPiece);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    continue;

                }

                // This is the pawn in passing special move..
                if ((sourcePiece.id == 1) &&
                     (destinationPiece.id == 1) &&
                      (sourcePiece.row == destinationPiece.row) &&
                       (previousMove.second == currentMove.second)) {


                    ChangeEveryThingAfterInPassingMove(currentMove, board,
                                                        whitePieces, blackPieces,
                                                         myColor, myScore,
                                                          opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    result = max(result, currentDifference);

                    ReturnEveryThingBeforeInPassingMove(currentMove, board,
                                                         whitePieces, blackPieces,
                                                          sourcePiece,
                                                           destinationPiece,
                                                            myColor, myScore,
                                                             opponentScore);

                    alpha = max(alpha, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MAX;
                    }

                    continue;

                }
                else if ((sourcePiece.id == 1) &&
                          (destinationPiece.id == 1) &&
                           (sourcePiece.row == destinationPiece.row)) {

                      continue;

                }

                MakeChanges(currentMove, board, whitePieces, blackPieces,
                             myColor, myScore, opponentScore);


                int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                result = max(result, currentDifference);

                ReturnEveryThingAsItWas(currentMove, sourcePiece,
                                         destinationPiece, board, whitePieces,
                                          blackPieces, myColor, myScore,
                                           opponentScore);


                alpha = max(alpha, currentDifference);
                if (beta <= alpha) {
                    numberOfCalculatedStatesNow++;
                    return INT_MAX;
                }

                }

            }

        }

        return result;

    }
    else {

        int result = INT_MAX;

        if (!myColor) {

            for (int i = 0; i < (int)blackPieces.size(); i++) {
                Piece currentPiece = blackPieces[i];

                if (!(board[currentPiece.row][currentPiece.column]
                    == currentPiece)) {
                    continue;
                }

                auto moves = GetMoves(currentPiece, board);

                for (auto currentMove : moves) {

                    Piece sourcePiece = board[currentMove.first.first]
                                          [currentMove.first.second];
                    Piece destinationPiece = board[currentMove.second.first]
                                                   [currentMove.second.second];

                    // I have to handle castling too..

                    // This is the returning case for white..
                    if ((sourcePiece.id == 1) && (currentMove.second.first == 8)) {

                    // Try returning the Queen..
                    HandleQueenReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }
                    // Try returning the Knight..
                    HandleKnightReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }

                    continue;

                }

                // This is the castling..
                if (sourcePiece.color == destinationPiece.color) {

                    ChangeEverThingAfterCastling(currentMove, board,
                                                  whitePieces, blackPieces,
                                                   sourcePiece, destinationPiece);


                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEverThingBeforeCastling(currentMove, board,
                                                   whitePieces, blackPieces,
                                                    sourcePiece, destinationPiece);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }

                    continue;

                }

                // This is the pawn in passing special move..
                if ((sourcePiece.id == 1) &&
                     (destinationPiece.id == 1) &&
                      (sourcePiece.row == destinationPiece.row) &&
                       (previousMove.second == currentMove.second)) {


                    ChangeEveryThingAfterInPassingMove(currentMove, board,
                                                        whitePieces, blackPieces,
                                                         myColor, myScore,
                                                          opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEveryThingBeforeInPassingMove(currentMove, board,
                                                         whitePieces, blackPieces,
                                                          sourcePiece,
                                                           destinationPiece,
                                                            myColor, myScore,
                                                             opponentScore);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }

                    continue;

                }
                else if ((sourcePiece.id == 1) &&
                          (destinationPiece.id == 1) &&
                           (sourcePiece.row == destinationPiece.row)) {

                      continue;

                }

                MakeChanges(currentMove, board, whitePieces, blackPieces,
                             myColor, myScore, opponentScore);


                int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                result = min(result, currentDifference);

                ReturnEveryThingAsItWas(currentMove, sourcePiece,
                                         destinationPiece, board, whitePieces,
                                          blackPieces, myColor, myScore,
                                           opponentScore);


                beta = min(beta, currentDifference);
                if (beta <= alpha) {
                    numberOfCalculatedStatesNow++;
                    return INT_MIN;
                }

                }

            }

        }
        else {

            for (int i = 0; i < (int)whitePieces.size(); i++) {
                Piece currentPiece = whitePieces[i];

                if (!(board[currentPiece.row][currentPiece.column]
                    == currentPiece)) {
                    continue;
                }

                auto moves = GetMoves(currentPiece, board);
                for (auto currentMove : moves) {

                    Piece sourcePiece = board[currentMove.first.first]
                                          [currentMove.first.second];
                    Piece destinationPiece = board[currentMove.second.first]
                                                   [currentMove.second.second];

                    // I have to handle castling too..

                    // This is the returning case for black..
                    if ((sourcePiece.id == 1) && (currentMove.second.first == 1)) {

                    // Try returning the Queen..
                    HandleQueenReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }
                    // Try returning the Knight..
                    HandleKnightReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);


                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }

                    continue;

                }

                // This is the castling..
                if (sourcePiece.color == destinationPiece.color) {

                    ChangeEverThingAfterCastling(currentMove, board,
                                                  whitePieces, blackPieces,
                                                   sourcePiece, destinationPiece);


                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEverThingBeforeCastling(currentMove, board,
                                                   whitePieces, blackPieces,
                                                    sourcePiece, destinationPiece);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }
                    continue;

                }

                // This is the pawn in passing special move..
                if ((sourcePiece.id == 1) &&
                     (destinationPiece.id == 1) &&
                      (sourcePiece.row == destinationPiece.row) &&
                       (previousMove.second == currentMove.second)) {


                    ChangeEveryThingAfterInPassingMove(currentMove, board,
                                                        whitePieces, blackPieces,
                                                         myColor, myScore,
                                                          opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    !myTurn, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    result = min(result, currentDifference);

                    ReturnEveryThingBeforeInPassingMove(currentMove, board,
                                                         whitePieces, blackPieces,
                                                          sourcePiece,
                                                           destinationPiece,
                                                            myColor, myScore,
                                                             opponentScore);

                    beta = min(beta, currentDifference);
                    if (beta <= alpha) {
                        numberOfCalculatedStatesNow++;
                        return INT_MIN;
                    }

                    continue;

                }
                else if ((sourcePiece.id == 1) &&
                          (destinationPiece.id == 1) &&
                           (sourcePiece.row == destinationPiece.row)) {

                      continue;

                }

                MakeChanges(currentMove, board, whitePieces, blackPieces,
                             myColor, myScore, opponentScore);


                int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                !myTurn, movesNumber - 1,
                                                 alpha, beta, currentMove);

                result = min(result, currentDifference);

                ReturnEveryThingAsItWas(currentMove, sourcePiece,
                                         destinationPiece, board, whitePieces,
                                          blackPieces, myColor, myScore,
                                           opponentScore);

                beta = min(beta, currentDifference);
                if (beta <= alpha) {
                    numberOfCalculatedStatesNow++;
                    return INT_MIN;
                }
                }

            }

        }

        return result;

    }

}


pair<pair<int, int>, pair<int, int>> Play(vector<vector<Piece>>& board,
                                           vector<Piece>& whitePieces,
                                            vector<Piece>& blackPieces,
                                             const bool& myColor,
                                              int movesNumber, int alpha, int beta,
                                               pair<pair<int, int>,
                                                pair<int, int>> previousMove) {

    numberOfCalculatedStatesNow = 0;

    int myScore = GetMyScore(whitePieces, blackPieces, myColor);
    int opponentScore = GetOpponentScore(whitePieces, blackPieces, myColor);

    pair<int, int> from;
    pair<int, int> to;
    int best = INT_MIN;

    vector<pair<pair<int, pair<pair<int, int>, pair<int, int>>> ,
            char>> allPossibleMoves;

    whatToReturn = '#';
    if (!myColor) {

        srand(unsigned(time(0)));
        random_shuffle(whitePieces.begin(), whitePieces.end());
        for (int i = 0; i < (int)whitePieces.size(); i++) {

            Piece currentPiece = whitePieces[i];
            auto moves = GetMoves(currentPiece, board);
            random_shuffle(moves.begin(), moves.end());
            for (auto currentMove : moves) {

                Piece sourcePiece = board[currentMove.first.first]
                                          [currentMove.first.second];
                Piece destinationPiece = board[currentMove.second.first]
                                               [currentMove.second.second];


                // This is the returning case for white..
                if ((sourcePiece.id == 1) && (currentMove.second.first == 1)) {

                    // Try returning the Queen..
                    HandleQueenReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                0, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = 'Q';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    // Try returning the Knight..
                    HandleKnightReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                0, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = 'K';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);


                    continue;

                }

                // This is the castling..
                if (sourcePiece.color == destinationPiece.color) {

                    ChangeEverThingAfterCastling(currentMove, board,
                                                  whitePieces, blackPieces,
                                                   sourcePiece, destinationPiece);


                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    0, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = '#';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEverThingBeforeCastling(currentMove, board,
                                                   whitePieces, blackPieces,
                                                    sourcePiece, destinationPiece);

                    continue;

                }

                // This is the pawn in passing special move..
                if ((sourcePiece.id == 1) &&
                     (destinationPiece.id == 1) &&
                      (sourcePiece.row == destinationPiece.row) &&
                       (previousMove.second == currentMove.second)) {

                    ChangeEveryThingAfterInPassingMove(currentMove, board,
                                                        whitePieces, blackPieces,
                                                         myColor, myScore,
                                                          opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    0, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = '#';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEveryThingBeforeInPassingMove(currentMove, board,
                                                         whitePieces, blackPieces,
                                                          sourcePiece,
                                                           destinationPiece,
                                                            myColor, myScore,
                                                             opponentScore);

                    continue;

                }
                else if ((sourcePiece.id == 1) &&
                          (destinationPiece.id == 1) &&
                           (sourcePiece.row == destinationPiece.row)) {

                      continue;

                }


                MakeChanges(currentMove, board, whitePieces, blackPieces,
                             myColor, myScore, opponentScore);


                int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                0, movesNumber - 1,
                                                 alpha, INT_MAX, currentMove);



                if (currentDifference >= best) {
                    best = currentDifference;
                    from = currentMove.first;
                    to = currentMove.second;
                    whatToReturn = '#';
                    allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                }
                alpha = max(alpha, currentDifference);

                ReturnEveryThingAsItWas(currentMove, sourcePiece,
                                         destinationPiece, board, whitePieces,
                                          blackPieces, myColor, myScore,
                                           opponentScore);

            }
        }


    }
    else {

        srand(unsigned(time(0)));
        random_shuffle(blackPieces.begin(), blackPieces.end());
        for (int i = 0; i < (int)blackPieces.size(); i++) {
            Piece currentPiece = blackPieces[i];

            auto moves = GetMoves(currentPiece, board);
            random_shuffle(moves.begin(), moves.end());
            for (auto currentMove : moves) {

                Piece sourcePiece = board[currentMove.first.first]
                                          [currentMove.first.second];
                Piece destinationPiece = board[currentMove.second.first]
                                               [currentMove.second.second];


                // This is the returning case for black..
                if ((sourcePiece.id == 1) && (currentMove.second.first == 8)) {

                    // Try returning the Queen..
                    HandleQueenReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                0, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = 'Q';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheQueenReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);

                    // Try returning the Knight..
                    HandleKnightReturningMoveChanges(currentMove, board,
                                                     whitePieces, blackPieces,
                                                      myColor, myScore,
                                                       opponentScore);

                    currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                0, movesNumber - 1,
                                                 alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = 'K';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEveryThingAsItWasBeforeTheKnightReturningMove(
                                           currentMove, sourcePiece,
                                            destinationPiece, board, whitePieces,
                                             blackPieces, myColor, myScore,
                                              opponentScore);


                    continue;

                }

                // This is the castling..
                if (sourcePiece.color == destinationPiece.color) {

                    ChangeEverThingAfterCastling(currentMove, board,
                                                  whitePieces, blackPieces,
                                                   sourcePiece, destinationPiece);


                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    0, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = '#';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEverThingBeforeCastling(currentMove, board,
                                                   whitePieces, blackPieces,
                                                    sourcePiece, destinationPiece);

                    continue;

                }

                // This is the pawn in passing special move..
                if ((sourcePiece.id == 1) &&
                     (destinationPiece.id == 1) &&
                      (sourcePiece.row == destinationPiece.row) &&
                       (previousMove.second == currentMove.second)) {


                    ChangeEveryThingAfterInPassingMove(currentMove, board,
                                                        whitePieces, blackPieces,
                                                         myColor, myScore,
                                                          opponentScore);

                    int currentDifference = Magic(board, whitePieces, blackPieces,
                                                   myColor, myScore, opponentScore,
                                                    0, movesNumber - 1,
                                                     alpha, beta, currentMove);

                    if (currentDifference >= best) {
                        best = currentDifference;
                        from = currentMove.first;
                        to = currentMove.second;
                        whatToReturn = '#';
                        allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                    }
                    alpha = max(alpha, currentDifference);

                    ReturnEveryThingBeforeInPassingMove(currentMove, board,
                                                         whitePieces, blackPieces,
                                                          sourcePiece,
                                                           destinationPiece,
                                                            myColor, myScore,
                                                             opponentScore);

                    continue;

                }
                else if ((sourcePiece.id == 1) &&
                          (destinationPiece.id == 1) &&
                           (sourcePiece.row == destinationPiece.row)) {

                      continue;

                }

                MakeChanges(currentMove, board, whitePieces, blackPieces,
                             myColor, myScore, opponentScore);

                int currentDifference = Magic(board, whitePieces, blackPieces,
                                               myColor, myScore, opponentScore,
                                                0, movesNumber - 1,
                                                 alpha, beta, currentMove);

                if (currentDifference >= best) {
                    best = currentDifference;
                    from = currentMove.first;
                    to = currentMove.second;
                    whatToReturn = '#';
                    allPossibleMoves.push_back({{currentDifference, {from, to}},
                                                      whatToReturn});
                }
                alpha = max(alpha, currentDifference);

                ReturnEveryThingAsItWas(currentMove, sourcePiece,
                                         destinationPiece, board, whitePieces,
                                          blackPieces, myColor, myScore,
                                           opponentScore);

            }

        }

    }

    if ((numberOfCalculatedStatesNow <=
          MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES) &&
           (best > 10000)) {

        theEngineWillWinForSure = 1;
        cout << "\n    Now, I will win whatever you will "
                        "play ;) ;) ;) ;) ;) .\n"
                        "    My move which will lead the board to "
                        "a 100% winning position for me:\n    ";

    }
    else if ((numberOfCalculatedStatesNow <=
             MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES) &&
             (best < -10000)) {

        theEngineWillWinForSure = 1;
        cout << "\n    You are a good player..\n    ";

    }

    vector<pair<pair<int, pair<pair<int, int>, pair<int, int>>> ,
            char>> bestPossibleMoves;
    for (auto current : allPossibleMoves) {
        if (current.first.first == best) {
            bestPossibleMoves.push_back(current);
        }
    }

    srand(time(0));
    int id = (((int)(rand())) % ((int)bestPossibleMoves.size()));

    if ((movesNumber >= NUMBER_OF_MOVES_TO_CALCULATE) &&
        (numberOfCalculatedStatesNow <= MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES)) {

            /*
            if (!theEngineWillWinForSure) {
                cout << "\n    The engine will play move number " << id + 1 <<
                    " from " << (int)bestPossibleMoves.size() <<
                    " available best moves, and it is:\n    ";
            }
            */


    }
    from = bestPossibleMoves[id].first.second.first;
    to = bestPossibleMoves[id].first.second.second;
    whatToReturn = bestPossibleMoves[id].second;

    return {from, to};

}


int GetMaximumNumberOfMoves(long long time, int moves) {

    int st = 1;
    int en = 1000;
    int averageMovesPerTurn;
    while (st <= en) {

        long long mid = (st + en) >> 1;
        long long current = 1;
        for (int i = 0; i < moves; i++) {
            current *= mid;
        }
        if (current <= time) {
            averageMovesPerTurn = mid;
            st = mid + 1;
        }
        else {
            en = mid - 1;
        }

    }

    int possibleMoves = 0;
    long long timeComplexity = 1;
    // The maximum reasonable number of moves to calculate is eight..
    for (int i = 0; i < 8; i++) {

        timeComplexity *= ((long long)(averageMovesPerTurn));
        if (timeComplexity > (MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES / 20)) {
            break;
        }

        possibleMoves++;

    }

    return possibleMoves;

}


bool ValidOpponentMove(const pair<int, int>& from,
                        const pair<int, int>& to,
                         vector<vector<Piece>>& board,
                          const vector<Piece>& whitePieces,
                           const vector<Piece>& blackPieces,
                            const bool& myColor) {



    if (!myColor) {

        for (Piece currentPiece : blackPieces) {
            auto moves = GetMoves(currentPiece, board);
            for (auto currentMove : moves) {
                if (currentMove == make_pair(from, to)) {
                    return 1;
                }
            }
        }

    }
    else {

        for (Piece currentPiece : whitePieces) {
            auto moves = GetMoves(currentPiece, board);
            for (auto currentMove : moves) {
                if (currentMove == make_pair(from, to)) {
                    return 1;
                }
            }
        }

    }

    return 0;

}


void ChangeEveryThingAfterThisMove(const pair<int, int>& from,
                                    const pair<int, int>& to,
                                     vector<vector<Piece>>& board,
                                      vector<Piece>& whitePieces,
                                       vector<Piece>& blackPieces) {

    bool color = board[from.first][from.second].color;
    if (whatToReturn == 'Q') {
        board[to.first][to.second] = Piece(5, 90, color, to.first, to.second, 0);
        board[from.first][from.second] = Piece();
    }
    else if (whatToReturn == 'K') {
        board[to.first][to.second] = Piece(2, 29, color, to.first, to.second, 0);
        board[from.first][from.second] = Piece();
    }
    // This means castling..
    else if (board[from.first][from.second].color ==
              board[to.first][to.second].color) {

        pair<pair<int, int>, pair<int, int>> currentMove = {from, to};
        Piece sourcePiece = board[from.first][from.second];
        Piece destinationPiece = board[to.first][to.second];
        ChangeEverThingAfterCastling(currentMove, board, whitePieces,
                                      blackPieces, sourcePiece, destinationPiece);

    }
    // This means the pawn in passing special move..
    else if ((board[from.first][from.second].id == 1) &&
             (from.first == to.first)) {

        if (!board[from.first][from.second].color) {
            board[to.first - 1][to.second] = board[from.first][from.second];
            board[to.first - 1][to.second].movesTillNow++;
            board[to.first - 1][to.second].row = to.first - 1;
            board[to.first - 1][to.second].column = to.second;
        }
        else {
            board[to.first + 1][to.second] = board[from.first][from.second];
            board[to.first + 1][to.second].movesTillNow++;
            board[to.first + 1][to.second].row = to.first + 1;
            board[to.first + 1][to.second].column = to.second;
        }
        board[from.first][from.second] = Piece();
        board[to.first][to.second] = Piece();

    }
    else {
        board[to.first][to.second] = board[from.first][from.second];
        board[to.first][to.second].movesTillNow++;
        board[to.first][to.second].row = to.first;
        board[to.first][to.second].column = to.second;
        board[from.first][from.second] = Piece();
    }

    whitePieces.clear();
    blackPieces.clear();
    for (int row = 1; row < 9; row++) {
        for (int col = 1; col < 9; col++) {
            if (board[row][col].id) {
                if (!board[row][col].color) {
                    whitePieces.push_back(board[row][col]);
                }
                else {
                    blackPieces.push_back(board[row][col]);
                }
            }
        }
    }

    whatToReturn = '#';

    lastMove = {from, to};

    return;

}


int main() {

    vector<vector<Piece>> board(9, vector<Piece>(9));
    vector<Piece> whitePieces;
    vector<Piece> blackPieces;

    Initialization(board, whitePieces, blackPieces);

    // "myColor" is 0 means that the computer is white..
    bool myColor = SayHello();

    // "turn" is 0 means that white should play in this turn..
    bool turn = 0;
    while (1) {

        if (myColor == turn) {

            cout << ENGINE_NAME << " engine move:\n    ";

            cout << ENGINE_NAME << " engine is calculating for " <<
                    NUMBER_OF_MOVES_TO_CALCULATE << " moves forward:\n    ";

            theEngineWillWinForSure = 0;
            auto result = Play(board, whitePieces, blackPieces, myColor,
                                NUMBER_OF_MOVES_TO_CALCULATE, INT_MIN, INT_MAX,
                                 lastMove);

            pair<int, int> from = result.first;
            pair<int, int> to = result.second;
            from = {8 - from.first + 1, from.second + ((int)('A')) - 1};
            to = {8 - to.first + 1, to.second + ((int)('A')) - 1};
            cout << "from " << (char)(from.second) << " " << from.first <<
                    "\n     to " << (char)to.second << " " <<
                    to.first << "\n\n";

            cout << "    The depth of the moves tree is: " <<
                    NUMBER_OF_MOVES_TO_CALCULATE << "\n"
                    "    The number of calculated final states is: " <<
                    numberOfCalculatedStatesNow << "\n\n    ";

            /*
            int tryMoreMoves = max(NUMBER_OF_MOVES_TO_CALCULATE,
                                    GetMaximumNumberOfMoves(
                                     numberOfCalculatedStatesNow,
                                      NUMBER_OF_MOVES_TO_CALCULATE));

            if (tryMoreMoves > NUMBER_OF_MOVES_TO_CALCULATE) {
                cout << "             ..........\n\n"
                        "    " << ENGINE_NAME << " engine is calculating for " <<
                        tryMoreMoves << " moves forward:\n    ";

                auto newResult = Play(board, whitePieces, blackPieces, myColor,
                               tryMoreMoves, INT_MIN, INT_MAX, lastMove);

                if (numberOfCalculatedStatesNow >
                     MAXIMUM_POSSIBLE_NUMBER_OF_FINAL_STATES) {

                    cout << "    " << ENGINE_NAME << " engine failed in"
                            "calculating for " << tryMoreMoves <<
                            " moves forward, so play the "
                            "previous game.\n";

                }
                else {

                    result = newResult;
                    from = result.first;
                    to = result.second;
                    from = {8 - from.first + 1, from.second + ((int)('A')) - 1};
                    to = {8 - to.first + 1, to.second + ((int)('A')) - 1};
                    cout << "from " << (char)(from.second) << " " << from.first <<
                            "\n     to " << (char)to.second << " " <<
                            to.first << "\n\n";

                    cout << "    The depth of the moves tree is: " <<
                            tryMoreMoves << "\n"
                            "    The number of calculated final states is: " <<
                            numberOfCalculatedStatesNow << "\n";

                }

            }
            */



            from = result.first;
            to = result.second;

            if (whatToReturn == 'Q') {
                cout << "\n    " << ENGINE_NAME << " engine promoted to a Queen.\n";
            }
            else if (whatToReturn == 'K') {
                cout << "\n    " << ENGINE_NAME << " engine promoted to a Knight.\n";
            }

            ChangeEveryThingAfterThisMove(from, to, board, whitePieces,
                                           blackPieces);



        }
        else {

            cout << "Your move:\n    ";
            int rowFrom;
            char chFrom;
            cout << "from" << " ";
            cin >> chFrom >> rowFrom;
            pair<int, int> from = {8 - rowFrom + 1, (int)(chFrom - 'A') + 1};

            cout << "     to ";
            int rowTo;
            char chTo;
            cin >> chTo >> rowTo;
            pair<int, int> to = {8 - rowTo + 1, (int)(chTo - 'A') + 1};

            if (!ValidOpponentMove(from, to, board,
                                    whitePieces, blackPieces, myColor)) {

                cout << "This is not a valid move ;) , please play again..\n\n";
                continue;

            }
            else if ((board[from.first][from.second].id == 1) &&
                      (from.first == to.first) &&
                       (lastMove.second != to)) {

                cout << "This is not a valid move ;) , please play again..\n\n";
                continue;

            }

            if (!myColor) {
                if ((board[from.first][from.second].id == 1) &&
                     (to.first == 8)) {

                    cout << "    If you want to promote to a Queen press "
                            "capital Q, to a Knight press capital K:\n    ";
                    cin >> whatToReturn;
                    cout << "\n";

                }
            }
            else {
                if ((board[from.first][from.second].id == 1) &&
                     (to.first == 1)) {

                    cout << "    If you want to promote to a Queen press "
                            "capital Q, to a Knight press capital K:\n    ";
                    cin >> whatToReturn;
                    cout << "\n";

                }
            }

            ChangeEveryThingAfterThisMove(from, to, board, whitePieces,
                                           blackPieces);

        }

        PrintTheBoard(board);

        /*
          Here after each turn I should check if there is a checkmate, and
          it is very easy just I can use the "Play" function..
        */

        cout << "          ##############################\n\n";

        turn = !turn;

    }

    return 0;

}


vector<pair<pair<int, int>, pair<int, int>>> GetMoves(
                                          const Piece& currentPiece,
                                           vector<vector<Piece>>& board) {

    vector<pair<pair<int, int>, pair<int, int>>> moves;

    pair<int, int> from = {currentPiece.row, currentPiece.column};
    pair<int, int> to;

    if (currentPiece.id == 1) {

        if (!currentPiece.color) {

            to = {from.first - 1, from.second};
            if (Valid(from, to, board) && (!board[to.first][to.second].id)) {
                moves.push_back({from, to});
            }

            to = {from.first - 1, from.second - 1};
            if (Valid(from, to, board) && (board[to.first][to.second].id)) {
                moves.push_back({from, to});
            }

            to = {from.first - 1, from.second + 1};
            if (Valid(from, to, board) && (board[to.first][to.second].id)) {
                moves.push_back({from, to});
            }

            if (currentPiece.row == 7) {
                to = {from.first - 2, from.second};
                if (Valid(from, to, board) &&
                    (!board[to.first][to.second].id) &&
                     (!board[from.first - 1][from.second].id)) {

                    moves.push_back({from, to});

                }
            }

        }
        else {

            to = {from.first + 1, from.second};
            if (Valid(from, to, board) && (!board[to.first][to.second].id)) {
                moves.push_back({from, to});
            }

            to = {from.first + 1, from.second - 1};
            if (Valid(from, to, board) && (board[to.first][to.second].id)) {
                moves.push_back({from, to});
            }

            to = {from.first + 1, from.second + 1};
            if (Valid(from, to, board) && (board[to.first][to.second].id)) {
                moves.push_back({from, to});
            }

            if (currentPiece.row == 2) {
                to = {from.first + 2, from.second};
                if (Valid(from, to, board) &&
                    (!board[to.first][to.second].id) &&
                     (!board[from.first + 1][from.second].id)) {

                    moves.push_back({from, to});

                }
            }

        }

        // And here is the special move for pawns..
        to = {from.first, from.second + 1};
        if (Valid(from, to, board) &&
            (board[to.first][to.second].id == 1) &&
             (board[to.first][to.second].movesTillNow == 1) &&
              ((to.first == 4) || (to.first == 5))) {

            if (!board[from.first][from.second].color) {
                if (!board[to.first - 1][to.second].id) {
                    moves.push_back({from, to});
                }
            }
            else {
                if (!board[to.first + 1][to.second].id) {
                    moves.push_back({from, to});
                }
            }

        }

        to = {from.first, from.second - 1};
        if (Valid(from, to, board) &&
            (board[to.first][to.second].id == 1) &&
             (board[to.first][to.second].movesTillNow == 1) &&
              ((to.first == 4) || (to.first == 5))) {

            if (!board[from.first][from.second].color) {
                if (!board[to.first - 1][to.second].id) {
                    moves.push_back({from, to});
                }
            }
            else {
                if (!board[to.first + 1][to.second].id) {
                    moves.push_back({from, to});
                }
            }
        }

    }
    else if (currentPiece.id == 2) {

        to = {from.first - 2, from.second - 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first - 2, from.second + 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first - 1, from.second - 2};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first - 1, from.second + 2};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 1, from.second - 2};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 1, from.second + 2};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 2, from.second - 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 2, from.second + 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

    }
    else if (currentPiece.id == 3) {

        for (int how = 1; how < 8; how++) {
            to = {from.first - how, from.second - how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int how = 1; how < 8; how++) {
            to = {from.first - how, from.second + how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int how = 1; how < 8; how++) {
            to = {from.first + how, from.second - how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int how = 1; how < 8; how++) {
            to = {from.first + how, from.second + how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

    }
    else if (currentPiece.id == 4) {

        for (int row = from.first - 1; row > 0; row--) {
            to = {row, from.second};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int row = from.first + 1; row < 9; row++) {
            to = {row, from.second};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int col = from.second - 1; col > 0; col--) {
            to = {from.first, col};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else if ((to.first > 0) && (to.first < 9) &&
                      (to.second > 0) && (to.second < 9) &&
                       (board[to.first][to.second].id == 6) &&
                        (board[from.first][from.second].color ==
                         board[to.first][to.second].color) &&
                          (!board[from.first][from.second].movesTillNow) &&
                           (!board[to.first][to.second].movesTillNow)) {

                 bool castling = 0;
                 if (!board[from.first][from.second].color) {

                    // This means long castling for white..
                    if (from.second == 1) {

                        castling = (IsThisCellSaveForWhite(board, {8, 3}) &&
                                     IsThisCellSaveForWhite(board, {8, 4}) &&
                                      IsThisCellSaveForWhite(board, {8, 5}));


                    }
                    // This means short castling for white..
                    else {

                        castling = (IsThisCellSaveForWhite(board, {8, 5}) &&
                                     IsThisCellSaveForWhite(board, {8, 6}) &&
                                      IsThisCellSaveForWhite(board, {8, 7}));

                    }

                 }
                 else {

                    // This means long castling for black..
                    if (from.second == 1) {

                        castling = (IsThisCellSaveForBlack(board, {1, 3}) &&
                                     IsThisCellSaveForBlack(board, {1, 4}) &&
                                      IsThisCellSaveForBlack(board, {1, 5}));

                    }
                    // This means short castling for black..
                    else {

                        castling = (IsThisCellSaveForBlack(board, {1, 5}) &&
                                     IsThisCellSaveForBlack(board, {1, 6}) &&
                                      IsThisCellSaveForBlack(board, {1, 7}));

                    }

                 }

                 if (castling) {
                    moves.push_back({from, to});
                 }
                 break;

            }
            else {
                break;
            }

        }

        for (int col = from.second + 1; col < 9; col++) {
            to = {from.first, col};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else if ((to.first > 0) && (to.first < 9) &&
                      (to.second > 0) && (to.second < 9) &&
                       (board[to.first][to.second].id == 6) &&
                        (board[from.first][from.second].color ==
                         board[to.first][to.second].color) &&
                          (!board[from.first][from.second].movesTillNow) &&
                           (!board[to.first][to.second].movesTillNow)) {

                 bool castling = 0;
                 if (!board[from.first][from.second].color) {

                    // This means long castling for white..
                    if (from.second == 1) {

                        castling = (IsThisCellSaveForWhite(board, {8, 3}) &&
                                     IsThisCellSaveForWhite(board, {8, 4}) &&
                                      IsThisCellSaveForWhite(board, {8, 5}));


                    }
                    // This means short castling for white..
                    else {

                        castling = (IsThisCellSaveForWhite(board, {8, 5}) &&
                                     IsThisCellSaveForWhite(board, {8, 6}) &&
                                      IsThisCellSaveForWhite(board, {8, 7}));

                    }

                 }
                 else {

                    // This means long castling for black..
                    if (from.second == 1) {

                        castling = (IsThisCellSaveForBlack(board, {1, 3}) &&
                                     IsThisCellSaveForBlack(board, {1, 4}) &&
                                      IsThisCellSaveForBlack(board, {1, 5}));

                    }
                    // This means short castling for black..
                    else {

                        castling = (IsThisCellSaveForBlack(board, {1, 5}) &&
                                     IsThisCellSaveForBlack(board, {1, 6}) &&
                                      IsThisCellSaveForBlack(board, {1, 7}));

                    }

                 }

                 if (castling) {
                    moves.push_back({from, to});
                 }
                 break;

            }
            else {
                break;
            }

        }

    }
    else if (currentPiece.id == 5) {

        // First exactly like the rook..
        for (int row = from.first - 1; row > 0; row--) {
            to = {row, from.second};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int row = from.first + 1; row < 9; row++) {
            to = {row, from.second};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int col = from.second - 1; col > 0; col--) {
            to = {from.first, col};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int col = from.second + 1; col < 9; col++) {
            to = {from.first, col};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        // And then like the Bishop..
        for (int how = 1; how < 8; how++) {
            to = {from.first - how, from.second - how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int how = 1; how < 8; how++) {
            to = {from.first - how, from.second + how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int how = 1; how < 8; how++) {
            to = {from.first + how, from.second - how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

        for (int how = 1; how < 8; how++) {
            to = {from.first + how, from.second + how};
            if (Valid(from, to, board)) {
                moves.push_back({from, to});
                if (board[to.first][to.second].id) {
                    break;
                }
            }
            else {
                break;
            }
        }

    }
    else {

        to = {from.first - 1, from.second - 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first - 1, from.second};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first - 1, from.second + 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first, from.second - 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first, from.second + 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 1, from.second - 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 1, from.second};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

        to = {from.first + 1, from.second + 1};
        if (Valid(from, to, board)) {
            moves.push_back({from, to});
        }

    }

    return moves;

}

