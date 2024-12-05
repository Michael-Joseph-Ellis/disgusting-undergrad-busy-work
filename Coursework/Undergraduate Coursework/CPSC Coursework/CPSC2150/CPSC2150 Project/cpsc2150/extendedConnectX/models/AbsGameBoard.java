package cpsc2150.extendedConnectX.models;

public abstract class AbsGameBoard implements IGameBoard
{
    private int dimensions;

    /**
     * Provides a string representation of the current game board.
     *
     * @return A formatted string that visually represents the board's current state.
     *
     * @pre The game board must be a 2D character array `char[][]`.
     *
     * @post The returned string representation retains the dimensions and values of the game board.
     */
    @Override
    public String toString() {
        StringBuilder boardString = new StringBuilder();

        boardString.append("|");
        for (int i = 0; i < getColumns(); i++) {
            boardString.append(String.format("%2d|", i));
        }
        boardString.append("\n");

        // Add each row of the board from top to bottom
        for (int r = 0; r < getRows(); r++) {
            boardString.append("|");
            for (int c = 0; c < getColumns(); c++) {
                boardString.append(String.format("%-2c|",  whatsAtPos(new BoardPosition(r, c)) ));
            }
            boardString.append("\n");
        }

        return boardString.toString();
    }
}