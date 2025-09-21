package cpsc2150.extendedConnectX.models;

/*

Michael Ellis - Michael-Joseph-Ellis

Ryan Chen - rchen55

Cooper Taylor - Cooper-Taylor

Adam Niemczura - AdamNiem

*/

/**
 * GameBoard is a concrete implementation of the AbsGameBoard class, implementing the IGameBoard interface.
 * It represents a grid-like game board for a ConnectX game, with defined operations for placing tokens
 * and checking for game conditions. Uses a 2D Array to represent the board.
 *
 * @corresponds:  self: board
 *                numRows: rows
 *                numCols: columns
 *                numToWin: number of tokens required to win
 *
 * @invariants: board is a MAX_ROW x MAX_COL grid and contains only ' ', 'X', or 'O' characters.
 */

public class GameBoard extends AbsGameBoard
{
    private final char[][] board;
    private int rows;
    private int columns;
    private int numToWin;

    /**
     * Constructor for the GameBoard class.
     * It initializes a game board with the specified rows, columns, and tokens needed to win.
     *
     * @param rows: the number of rows for the game board
     * @param columns: the number of columns for the game board
     * @param numToWin: the number of tokens needed to win the game
     *
     * @pre [min num of rows allowed] <= rows <= [max num of rows allowed]
     *      AND [min num of columns allowed] <= columns <= [max num of columns allowed]
     *      AND [min num to win allowed] <= numToWin <= [max num to win allowed]
     *      AND numToWin <= rows
     *      AND numToWin <= columns
     *
     * @post A new game board of size rows x columns is initialized with all empty spaces (' ').
     *       The winning condition is set to numToWin.
     */
    public GameBoard(int rows, int columns, int numToWin) {
       this.rows = rows;
       this.columns = columns;
       this.numToWin = numToWin;
       board = new char[rows][columns];

       // Initialize the board with empty spaces
       for (int r = 0; r < rows; r++) {
           for (int c = 0; c < columns; c++) {
               board[r][c] = ' ';
           }
       }
   }

    /**
     * A dynamic constructor for GameBoard letting you pass the initial board state. Useful for test cases
     *
     * @param initialBoard the initial board state as a char[][]
     *
     * @pre [num rows of initialBoard] = [number of rows] AND [num columns of initialBoard] = [number of columns]
     *
     * @post A new GameBoard is initialized with a board equivalent to the initialBoard specified.
     */
    // Initialize the board with the passed values
    public GameBoard(char[][] initialBoard)
    {
        this.board = initialBoard; 
    }

    // Returns the number of columns on the game board.
    @Override
    public int getRows()
    {
        return rows;
    }
    
    // Returns the number of rows on the game board.
    @Override
    public int getColumns()
    {
        return columns;
    }

    // Returns the number of tokens in a row needed to win the game.
    @Override
    public int getNumToWin()
    {
        return numToWin;
    }

    // Places the character p in column c. The token will be placed in the lowest available row in column c.
    @Override // Now override because we are implementing an interface
    public void dropToken(char p, int c)
    {
        for (int r = rows - 1; r >= 0; r--)
        {
            if (board[r][c] == ' ')
            {
                board[r][c] = p; // place the token
                break;
            }
        }
    }
    
    // Returns what is in the GameBoard at position pos If no marker is there, it returns a blank space char.
    @Override // Now override because we are implementing an interface
    public char whatsAtPos(BoardPosition pos)
    {   
        return board[pos.getRow()][pos.getColumn()];
    }
}