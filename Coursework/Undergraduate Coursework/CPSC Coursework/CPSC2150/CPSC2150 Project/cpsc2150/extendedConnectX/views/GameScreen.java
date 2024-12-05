package cpsc2150.extendedConnectX.views;

import cpsc2150.extendedConnectX.models.GameBoard;
import cpsc2150.extendedConnectX.models.GameBoardMem;
import cpsc2150.extendedConnectX.models.IGameBoard;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;

/*

Michael Ellis - Michael-Joseph-Ellis

Ryan Chen - rchen55

Cooper Taylor - Cooper-Taylor

Adam Niemczura - AdamNiem

*/

/**
 * The `GameScreen` class is responsible for handling the user interface
 * and game loop for a Connect X game.
 * It provides methods for printing the game board, checking for game end conditions,
 * getting user input, and prompting the player for their move.
 */
 public class GameScreen {

    /*
     * NOTE: 
     * The current driver is most likely too long to be viable. In other words, the current
     * implemented driver is just for test and should probably be broken down.
     * This is project has yet to have the new implementation of the GameBoardMem class, however I've added in the 
     * if statement to check if the game mode is memory efficient or not.  
     */

    /**
     * Main function which is the starting point for running.
     *
     * @param args holds any arguments passed when running the program
     *
     * @pre [BufferedReader is available] AND [computer running the program has visual console to output and input]
     *
     * @post self = #self AND [runs the game]
     *
     * @throws IOException if IO error occurs
     *
     */

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        boolean gameEnded; // Main game loop control

        do {
            // Setup game
            int numPlayers = getNumPlayers(reader);
            char[] playerTokens = getPlayerTokens(reader, numPlayers);
            int[] boardConfig = getBoardConfig(reader);
            int rows = boardConfig[0], columns = boardConfig[1], numToWin = boardConfig[2];
            IGameBoard gameBoard = selectGameMode(reader, rows, columns, numToWin);

            // Play game
            playGame(reader, gameBoard, playerTokens, gameBoard.getColumns());

            // Check replay
            gameEnded = !promptReplay(reader);
        } while (!gameEnded);
    }

    /**
     * Prompts the user to enter the number of players and validates the input.
     * The number of players must be between 2 and 10, inclusive.
     *
     * @param reader the BufferedReader used to read the user's input
     *
     * @pre [reader exists and is provided as a parameter]
     *      AND [user input to reader data type is some integer]
     *      AND [min number of players allowed] <= [user input to reader] <= [max number of players allowed]
     *
     * @post self = #self AND [returns the user inputted number of players requested]
     *
     * @throws IOException if IO error occurs
     * 
     * @return the number of players as an integer
     */
    private static int getNumPlayers(BufferedReader reader) throws IOException {
        System.out.println("How many players?");
        return Integer.parseInt(getValidatedInput(reader, "Must be between 2 and 10", input ->
                input.matches("\\d+") && Integer.parseInt(input) >= 2 && Integer.parseInt(input) <= 10));
    }

    /**
     * Prompts each player for their token and ensures no duplicate tokens are used.
     *
     * @param reader the BufferedReader used to read the user's input
     * @param numPlayers the number of players currently playing
     *
     * @pre [user input is some character]
     *
     * @post self = #self AND [returns the players' tokens inputted as an array of characters]
     *       AND [print to screen for user input]
     *       AND [print to screen if player(s) pick a token that's already chosen]
     *
     * @throws IOException if IO error occurs
     *
     * @return character array
     */
    private static char[] getPlayerTokens(BufferedReader reader, int numPlayers) throws IOException {
        char[] playerTokens = new char[numPlayers];
        Set<Character> usedTokens = new HashSet<>();

        for (int i = 0; i < numPlayers; i++) {
            System.out.printf("Enter the character to represent player %d\n", i + 1);
            char token;

            while (true) {
                String input = getValidatedInput(reader, "Enter a single letter character.", str ->
                        str.length() == 1 && Character.isLetter(str.charAt(0)));
                token = Character.toUpperCase(input.charAt(0));

                if (usedTokens.contains(token)) {
                    System.out.println(token + " is already taken as a player token!");
                    System.out.printf("Enter the character to represent player %d\n", i + 1);
                } else {
                    usedTokens.add(token);
                    break;
                }
            }
            playerTokens[i] = token;
        }
        return playerTokens;
    }

    /**
     * Prompts the user to input the board configuration including the number of rows, columns, and the number of
     * consecutive pieces needed to win. The inputs are validated to ensure they fall within specified ranges.
     *
     * @param reader the BufferedReader used to read user input
     *
     * @pre [reader exists]
     *
     * @post [prompts user for number of rows, columns, and number in a row to win]
     *       AND ([returns the user inputted number of rows, columns, and number in a row to win]
     *
     * @throws IOException if IO error occurs
     * 
     * @return an array containing the number of rows, columns, and the number of consecutive pieces needed to win
     * 
     */
    
    private static int[] getBoardConfig(BufferedReader reader) throws IOException {
        System.out.println("How many rows should be on the board?");
        int rows = Integer.parseInt(getValidatedInput(reader, "Must be between 3 and 100", input ->
                input.matches("\\d+") && Integer.parseInt(input) >= 3 && Integer.parseInt(input) <= 100));

        System.out.println("How many columns should be on the board?");
        int columns = Integer.parseInt(getValidatedInput(reader, "Must be between 3 and 100", input ->
                input.matches("\\d+") && Integer.parseInt(input) >= 3 && Integer.parseInt(input) <= 100));

        System.out.println("How many in a row to win?");
        int numToWin = Integer.parseInt(getValidatedInput(reader, "Must be between 3 and 25 and less than rows and columns", input ->
                input.matches("\\d+") && Integer.parseInt(input) >= 3 && Integer.parseInt(input) <= 25 &&
                        Integer.parseInt(input) <= rows && Integer.parseInt(input) <= columns));

        return new int[]{rows, columns, numToWin};
    }

    /**
     * Prompts the user to select a game mode and returns the corresponding game board.
     *
     * @param reader the BufferedReader to read user input
     * @param rows the number of rows for the game board
     * @param columns the number of columns for the game board
     * @param numToWin the number of consecutive markers needed to win
     *
     * @pre [min rows allowed] <= rows <= [max rows allowed]
     *      AND [min columns allowed] <= columns <= [max columns allowed]
     *      AND [min number to win allowed] <= numToWin <= [max number to win allowed]
     *
     * @post [returns a new instance of the fast game board] OR [returns a new instance of the memory efficient game board]
     *
     * @throws IOException if IO error occurs
     * 
     * @return an instance of IGameBoard based on the selected game mode
     * 
     */
    
    private static IGameBoard selectGameMode(BufferedReader reader, int rows, int columns, int numToWin) throws IOException {
        System.out.println("Would you like a Fast Game (F/f) or a Memory Efficient Game (M/m)?");
        String gameMode = getValidatedInput(reader, "Enter F or M", input ->
                input.equalsIgnoreCase("f") || input.equalsIgnoreCase("m"));

        if (gameMode.equalsIgnoreCase("f")) {
            return new GameBoard(rows, columns, numToWin);
        } else {
            return new GameBoardMem(rows, columns, numToWin);
        }
    }

    /**
     * Play game loop for the connectX game.
     *
     * @param reader       the BufferedReader to read user input
     * @param gameBoard    the game board where the game is played
     * @param playerTokens an array of characters representing the players' tokens
     * @param columns      the number of columns in the game board
     *
     * @pre [reader exists] AND [gameBoard] AND [playerTokens contains valid player tokens based on the tokens players chose]
     *      AND [min number of columns allowed] <= columns <= [max number of columns allowed]
     *
     * @post [game of connect 4 has been played]
     *
     * @throws IOException if IO error occurs
     *
     */

    private static void playGame(BufferedReader reader, IGameBoard gameBoard, char[] playerTokens, int columns) throws IOException {
        boolean roundEnded = false;
        int turnCounter = 0;

        while (!roundEnded) {
            printBoard(gameBoard);

            char currentPlayer = playerTokens[turnCounter % playerTokens.length];
            System.out.printf("Player %c, what column do you want to place your marker in?\n", currentPlayer);

            int column = Integer.parseInt(getValidatedInput(reader, "Column out of bounds. Try again.", input ->
                    input.matches("\\d+") && Integer.parseInt(input) >= 0 && Integer.parseInt(input) < columns));

            gameBoard.dropToken(currentPlayer, column);

            roundEnded = checkGameEnd(gameBoard, column, currentPlayer);
            turnCounter++;
        }
    }

    /**
     * Prompts the user to decide if they want to play again and returns their response.
     *
     * @param reader the BufferedReader to read user input from
     *
     * @pre [reader exists]
     *
     * @post true if the user wants to play again, false otherwise
     *       AND [outputted prompt to console asking to play again]
     *
     * @throws IOException if IO error occurs
     *
     * @return boolean
     */
    
    private static boolean promptReplay(BufferedReader reader) throws IOException {
        System.out.println("Would you like to play again? Y/N");
        String playAgain = getValidatedInput(reader, "Enter Y or N", input ->
                input.equalsIgnoreCase("y") || input.equalsIgnoreCase("n"));
        return playAgain.equalsIgnoreCase("y");
    }

    /**
     * Displays the current state of the game board in the console.
     *
     * @param gameBoard The game board object implementing the IGameBoard interface.
     *
     * @pre gameBoard != null
     *      AND [gameBoard.toString() produces a string representation of the game board with correct dimensions.]
     *
     * @post The game board's current state is printed to the console.
     *       AND gameBoard == #gameBoard.
     *
     */

    public static void printBoard(IGameBoard gameBoard)
    {
        System.out.println(gameBoard.toString());
    }

    /**
     * Evaluates whether the game has ended due to a win or a tie and handles post-game actions.
     * If the game has ended, it prints the game outcome.
     *
     * @param gameBoard The game board object representing the current state of the game.
     * @param column The column index where the last token was placed.
     * @param player The character representing the current player.
     *
     * @pre gameBoard != null
     *      AND 0 <= column < [max number of columns of gameBoard]
     *      AND [gameBoard.checkForWin(column) and gameBoard.checkTie() are valid methods]
     *
     * @post [If the game ends, a message indicating the outcome (win or tie) is printed]
     *       AND self = #self AND [return true if round ends, else return false]
     *
     * @return boolean
     */

    public static boolean checkGameEnd(IGameBoard gameBoard, int column, char player)
    {
        if (gameBoard.checkForWin(column))
        {
            System.out.printf("Player %c Won!\n", player);
            return true; // Round ends
        }
        else if (gameBoard.checkTie())
        {
            System.out.println("It's a tie!");
            return true; // Round ends
        }
        return false; // Round continues
    }

    /**
     * Validates user input based on a specified condition and provides feedback for invalid inputs.
     *
     * @param reader The `BufferedReader` used to read user input from the console.
     * @param errorMessage The error message to display when the input does not satisfy the validation condition.
     * @param condition A `Predicate<String>` representing the condition the input must satisfy to be considered valid.
     *
     * @pre reader != null
     *      AND errorMessage != null
     *      AND condition != null
     *      AND reader is ready to read input from the user.
     *
     * @post [Returns a valid input string that satisfies the given condition]
     *       AND [If invalid input is provided, the error message is displayed, and the user is prompted again until valid input is received]
     *
     * @throws IOException If an I/O error occurs while reading user input.
     *
     * @return String
     */
    private static String getValidatedInput(BufferedReader reader, String errorMessage, java.util.function.Predicate<String> condition) throws IOException
    {
        while (true)
        {
            String input = reader.readLine().trim();
            if (condition.test(input))
            {
                return input;
            }
            System.out.println(errorMessage);
        }
    }
}