package cpsc2150.extendedConnectX.models;

/*

Michael Ellis - Michael-Joseph-Ellis

Ryan Chen - rchen55

Cooper Taylor - Cooper-Taylor

Adam Niemczura - AdamNiem

 */

public class BoardPosition
{
    private final int Row;
    private final int Column;

    /**
     * A parameterized constructor for BoardPosition, accepts 2 integers
     * 
     * @param aRow the value of a row on the game board 
     * @param aColumn the value of a column on the game board
     * 
     * @return getRow = aRow AND row = #aRow AND getColumn = aColumn AND column = #aColumn
     *
     * @pre aRow >= 0 AND aColumn >= 0
     * 
     * @post this.Row = aRow AND this.Column = aColumn
     * 
     */
    
    // Parameterized constructor for BoardPosition
    public BoardPosition(int aRow, int aColumn)
    {   
        this.Row = aRow;
        this.Column = aColumn;
    }

    /**
     * Standard getter for the row of the board position 
     *
     * @return the row of the board position 
     * 
     * @pre this != null
     * 
     * @post getRow = #Row AND Row = #Row AND Column = #Column
     * 
     */

    public int getRow()
    {
        return this.Row; //returns the row
    }

    /**
     * Standard getter for the column of the board position
     * 
     * @return the column of the board position 
     * 
     * @pre this != null
     * 
     * @post getColumn = #Column AND Row = #Row AND Column = #Column
     * 
     */

    public int getColumn()
    {
        return this.Column; //returns the column
    }

    /**
     * Standard override for the equals method
     * 
     * @param obj the BoardPosition object to compare to
     * 
     * @return true OR false AND obj = #obj AND Row = #Row AND Column = #Column
     * 
     * @pre obj != null
     * 
     * @post  returns true IF (this.getColumn() == obj.getColumn() AND this.getRow() == obj.getRow())
     * ELSE returns false.
     * obj = #obj AND Row = #Row AND Column = #Column
     *
     */

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;
        if (getClass() != obj.getClass()) return false;
        BoardPosition o = (BoardPosition) obj;
        return Row == o.Row && Column == o.Column;
    }

    /**
     * Standard override for the toString method
     * 
     * @return the string representation of the board position
     * 
     * @pre this != null
     * 
     * @post toString =  this.Row + "," + this.Column AND Column = #Column AND Row = #Row
     */

    @Override
    public String toString()
    {
        return Row + "," + Column;
    }
}