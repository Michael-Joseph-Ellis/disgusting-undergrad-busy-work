package cpsc2150.extendedConnectX.models;

import java.util.*;

/*

Ryan Chen - rchen55

Cooper Taylor - Cooper-Taylor

Michael Ellis - Michael-Joseph-Ellis

Adam Niemczura - AdamNiem

*/

/**
 * The GameBoardMem class is a memory-efficient implementation of the game board.
 * It uses a Map to store the positions of tokens for each player, instead of a 2D array.
 * Each key in the Map represents a player, and the value is a List of BoardPositions occupied by that player.
 *
 * @correspondence: self = board
 *                  numRows: rows
 *                  numCols: columns
 *                  numToWin: number of tokens required to win
 *
 * @invariants: board is a MAX_ROW x MAX_COL grid and contains only characters for each player's token.
 */
public class GameBoardMem extends AbsGameBoard 
{
    // Map to store player tokens and their positions on the board 
    private final Map<Character, List<BoardPosition>> board;

    private final int rows;
    private final int columns;
    private final int numToWin;

    // Constructor

    /**
     * Constructor for the GameBoardMem class.
     * @param rows the number of rows in the board (must be > 0)
     * @param columns the number of columns in the board (must be > 0)
     * @param numToWin the number of tokens in a row required to win (must be > 0 AND <= rows OR columns)
     * @throws IllegalArgumentException if rows, columns, or numToWin are invalid
     *
     * @pre [min rows allowed] <= rows <= [max rows allowed] AND
     *      [min columns allowed] <= columns <= [max columns allowed]
     *      AND [min num to win allowed] <= numToWin <= [max num to win allowed]
     *      AND numToWin <= rows AND numToWin <= columns
     * @post A new game board of size rows x columns is initialized with all empty spaces (' ').
     *       The winning condition is set to numToWin.
     */

    public GameBoardMem(int rows, int columns, int numToWin){
        this.rows = rows;
        this.columns = columns;
        this.numToWin = numToWin;
        this.board = new HashMap<Character, List<BoardPosition>>();
    }

    /**
     * Places a token for the specified player in the given column
     *
     * @param p the player token (must be a valid character)
     * @param c the column index (0 <= c < columns
     *
     */
    @Override
    public void dropToken(char p, int c) {
        // Gravity-fy token
        int row = rows - 1;
        while (row >= 0 && whatsAtPos(new BoardPosition(row, c)) != ' ') {
            row--;
        }

        // Add board position
        if (row >= 0) {
            if (!board.containsKey(p)) {
                board.put(p, new Vector<BoardPosition>());
            }

            board.get(p).add(new BoardPosition(row, c));
        }
    }

    /**
     * Checks what token is at the specified board position
     *
     * @param pos the board position to check (row and column indices must be valid)
     * @return the character token at the position, or ' ' if the position is empty
     */
    @Override
    public char whatsAtPos(BoardPosition pos) {
        for (Map.Entry<Character, List<BoardPosition>> entry : board.entrySet()){
            if (entry.getValue().contains(pos)){
                return entry.getKey();
            }
        }
        return ' ';
    }

    @Override
    public int getRows() {
        return rows;
    }

    @Override
    public int getColumns() {
        return columns;
    }

    @Override
    public int getNumToWin() {
        return numToWin;
    }
}