package cpsc2150.extendedConnectX.models;

/**
 *  iGameBoard interface for GameBoard operations checkIfFree, dropToken,
 *  checkForWin, checkTie, checkHorizWin, checkDiagWin, whatsAtPos, and isPlayerAtPos.
 *  A grid starting at Index 0.
 *
 * @initialization_ensures: board contains only ' ' characters
 *  and is MAX_ROW x MAX_COL or smaller
 *
 * @defines: self: the board
 *           numRows: number of rows in self
 *           numCol: number of columns in self
 *           tokensToWin: number of tokens required to win
 *
 * @constraints: [Pieces must abide by gravity (so no empty position can exist vertically between two pieces)]
 *               AND [each player will only place one piece per turn]
 *
 */

public interface IGameBoard {
    public static final int MAX_ROW = 9;
    public static final int MAX_COL = 7;
    public static final int TOKENS_TO_WIN = 5;

    /**
     * A checker to see if a column has a free space, accepts 1 int param
     *
     * @param c the index of the column on self to check
     *
     * @return true IF [the column is free] AND false IF [column is full]
     *
     * @pre 0 <= c < [number of columns]
     *
     * @post checkIfFree = true if column c contains at least one ' ' character;
     *       checkIfFree = false if all positions in column c are filled with tokens.
     *       AND self = #self
     */
    default boolean checkIfFree(int c){
        return whatsAtPos(new BoardPosition(0,c)) == ' ';
    }

    /**
     * Places the token in the lowest available row in column c.
     *
     * @param p the character representing the player's token
     * @param c the index of the column on the game board
     *
     * @pre 0 <= c < MAX_COL AND checkIfFree(c) = true AND p is not null
     *
     * @post The token `p` is added to the lowest available row in column `c` on the game board.
     *       AND the state of the game board is updated to reflect this change.
     *       AND self = #self with the updated board.
     */

    // Primary - needs to access board so change can be made
    void dropToken(char p, int c);

    /**
     * Checks if the last token placed in the specified column resulted in a win.
     *
     * @param c the index of the column where the last token was placed
     *
     * @return true IF [last token in c results in a win] ELSE false
     *
     * @pre 0 <= c < getColumns() AND [the last move was made in column c]
     *
     * @post checkForWin = true if the last token in column c forms a winning sequence
     *       in any direction (horizontal, vertical, or diagonal);
     *       checkForWin = false otherwise.
     *       AND self = #self
     */
    // Secondary, just call other check win methods
    default boolean checkForWin(int c) {
        // Ensure the column index is valid
        assert c >= 0 && c < getColumns() : "Invalid column index";

        int row = 0;

        // Find the first occupied row in the given column
        while (row < getRows() && whatsAtPos(new BoardPosition(row, c)) == ' ') {
            row++;
        }

        // If no token was found in the column, no win is possible
        if (row >= getRows()) {
            return false;
        }

        char player = whatsAtPos(new BoardPosition(row, c));
        BoardPosition currentPos = new BoardPosition(row, c);

        // Check for win conditions
        return checkHorizWin(currentPos, player) || checkVertWin(currentPos, player) || checkDiagWin(currentPos, player);
    }

    // As long as we have MAX values, we can iterate and ensure all positions are filled
    // So secondary

    /**
     * Checks to see if the game has resulted in a tie
     *
     * @return true IF [all cells in board are filled] ELSE false
     *
     * @pre None
     *
     * @post checkTie = true if all cells in self are filled with tokens and no player has won;
     *       checkTie = false if there are any empty spaces or if a player has achieved a win.
     *       AND self = #self
     */
    default boolean checkTie(){
        for (int r = 0; r < getRows(); r++){
            for (int c =0; c < getColumns(); c++){
                if (whatsAtPos(new BoardPosition(r,c)) == ' ')
                    return false;
            }
        }
        return true;
    }

    /**
     * Checks to see if the last token placed resulted in a horizontal win
     *
     * @param pos the position where the last token was placed
     * @param p player who placed the last token
     *
     * @return true if the last token placed results in a horizontal win (a sequence of tokens matching `p`
     *         with length equal to or greater than `getNumToWin()`) in the same row as `pos`.
     *         Returns false otherwise.
     *
     * @pre pos != null
     *      AND 0 <= pos.getRow() < getRows()
     *      AND 0 <= pos.getColumn() < getColumns()
     *      AND p is not null
     *
     * @post checkHorizWin = true if there is a sequence of `getNumToWin()` or more consecutive tokens
     *       matching `p` in the same row as `pos`; otherwise, checkHorizWin = false.
     *       AND the game board remains unchanged (self = #self).
     */

    // Like checkTie, we can just use whatsAtPos so Secondary
    default boolean checkHorizWin(BoardPosition pos, char p) {
        int count = 1;

        // Check left
        for (int col = pos.getColumn() - 1; col >= 0; col--) {
            if (whatsAtPos(new BoardPosition(pos.getRow(), col)) == p) {
                count++;
                if (count >= getNumToWin()) { // Use dynamic value from getNumToWin()
                    return true;
                }
            } else {
                break;
            }
        }

        // Check right
        for (int col = pos.getColumn() + 1; col < getColumns(); col++) {
            if (whatsAtPos(new BoardPosition(pos.getRow(), col)) == p) {
                count++;
                if (count >= getNumToWin()) {
                    return true;
                }
            } else {
                break;
            }
        }
        return false;
    }

    /**
     * Checks to see if the last token placed resulted in a vertical win
     *
     * @param pos the position where the last token was placed
     * @param p the player who placed the last token
     *
     * @return true if the last token placed results in a vertical win (a sequence of tokens matching `p`
     *         with length equal to or greater than `getNumToWin()`) in the same column as `pos`.
     *         Returns false otherwise.
     *
     * @pre pos != null
     *      AND 0 <= pos.getRow() < getRows()
     *      AND 0 <= pos.getColumn() < getColumns()
     *      AND p is not null
     *
     * @post checkVertWin = true if there is a sequence of `getNumToWin()` or more consecutive tokens
     *       matching `p` in the same column as `pos`; otherwise, checkVertWin = false.
     *       AND the game board remains unchanged (self = #self).
     */
    // Secondary (same reasoning)
    default boolean checkVertWin(BoardPosition pos, char p) {
        int count = 1;

        // Check down
        for (int i = 1; i < getNumToWin(); i++) {
            int newRow = pos.getRow() + i;
            if (newRow >= getRows() || whatsAtPos(new BoardPosition(newRow, pos.getColumn())) != p) {
                break;
            }
            count++;
        }

        // Check up
        for (int i = 1; i < getNumToWin(); i++) {
            int newRow = pos.getRow() - i;
            if (newRow < 0 || whatsAtPos(new BoardPosition(newRow, pos.getColumn())) != p) {
                break;
            }
            count++;
        }

        return count >= getNumToWin();
    }

    /**
     * Checks to see if the last token placed resulted in a diagonal win
     *
     * @param pos the position where the last token was placed
     * @param p the player who placed the last token
     *
     * @return true if the last token placed results in a diagonal win (a sequence of tokens matching `p`
     *         with length equal to or greater than `getNumToWin()`) along either diagonal direction (\ or /).
     *         Returns false otherwise.
     *
     * @pre pos != null
     *      AND 0 <= pos.getRow() < getRows()
     *      AND 0 <= pos.getColumn() < getColumns()
     *      AND p is not null
     *
     * @post checkDiagWin = true if there is a sequence of `getNumToWin()` or more consecutive tokens
     *       matching `p` along either diagonal direction (\ or /); otherwise, checkDiagWin = false.
     *       AND the game board remains unchanged (self = #self).
     */
    // Secondary (same reasoning)
    default boolean checkDiagWin(BoardPosition pos, char p) {
        int row = pos.getRow();
        int col = pos.getColumn();
        int count = 1; // Start with the token at (row, col)

        // Check the main diagonal (\)
        // Count upwards-left (-1, -1)
        int tempRow = row - 1;
        int tempCol = col - 1;


        while (tempRow >= 0 && tempCol >= 0) {
            if (whatsAtPos(new BoardPosition(tempRow, tempCol)) == p) {
                count++;
                if (count >= getNumToWin()) {
                    return true;
                }
            } else {
                break;
            }
            tempRow--;
            tempCol--;
        }

        // Count downwards-right (+1, +1)
        tempRow = row + 1;
        tempCol = col + 1;

        while (tempRow < getRows() && tempCol < getColumns()) {
            if (whatsAtPos(new BoardPosition(tempRow, tempCol)) == p) {
                count++;
                if (count >= getNumToWin()) {
                    return true;
                }
            } else {
                break;
            }
            tempRow++;
            tempCol++;
        }

        // Reset count for the anti-diagonal (/)
        count = 1;

        // Check the anti-diagonal (/)
        // Count upwards-right (-1, +1)
        tempRow = row - 1;
        tempCol = col + 1;

        while (tempRow >= 0 && tempCol < getColumns()) {
            if (whatsAtPos(new BoardPosition(tempRow, tempCol)) == p) {
                count++;
                if (count >= getNumToWin()) {
                    return true;
                }
            } else {
                break;
            }
            tempRow--;
            tempCol++;
        }

        // Count downwards-left (+1, -1)
        tempRow = row + 1;
        tempCol = col - 1;

        while (tempRow < getRows() && tempCol >= 0) {
            if (whatsAtPos(new BoardPosition(tempRow, tempCol)) == p) {
                count++;
                if (count >= getNumToWin()) {
                    return true;
                }
            } else {
                break;
            }
            tempRow++;
            tempCol--;
        }

        // Return false if no win is found on either diagonal
        return false;
    }

    /**
     * Retrieves the character at a specific position on the board.
     *
     * @param pos a position on the game board
     *
     * @return the character present at the specified position.
     *
     * @pre 0 <= pos.getRow() < getRows() 0 <= pos.getColumn() < getColumns()
     *
     * @post returns the character at the specified position
     *       AND self = #self
     */

    // Primary - needs access to board
    char whatsAtPos(BoardPosition pos);

    /**
     * Returns boolean on whether a specified player is at a specified position on the board
     *
     * @param pos a position on the game board
     * @param player the name of the player we are evaluating
     *
     * @return boolean on whether a specified player is at a specified position on the board
     *
     * @pre 0 <= pos.getRow() < [number of rows] AND 0 <= pos.getColumn() < [number of columns] AND player is some real player
     *
     * @post isPlayerAtPos = true if self at pos contains the token of player;
     *       isPlayerAtPos = false if the token at pos does not match player.
     *       AND self = #self
     */
    // Secondary - only needs whatsAtPos
    default boolean isPlayerAtPos(BoardPosition pos, char player){
        return whatsAtPos(pos) == player;
    }

    /**
     * Returns the number of rows on the game board.
     *
     * @return the number of rows on the game board
     *
     * @pre None
     *
     * @post getRows = [the total number of rows specified for the game board during initialization]
     *       AND self = #self
     */
    // Primary - Needs to access private data
    int getRows();

    /**
     * Returns the number of columns on the game board.
     *
     * @return the number of columns on the game board
     *
     * @pre None
     *
     * @post getColumns = [the total number of columns specified for the game board during initialization]
     *       AND self = #self
     */
    // Primary - Needs to access private data
    int getColumns();

    /**
     * Returns the number of tokens required in a row to win the game.
     *
     * @return The number of tokens needed to win the game.
     *
     * @pre None
     * @post getNumToWin = [the required number of tokens to win]
     */
    // Primary - Needs to access private data
    int getNumToWin();
}