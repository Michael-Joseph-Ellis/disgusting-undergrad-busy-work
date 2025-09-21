package cpsc2150.observer;

import cpsc2150.subject.MyInteger;

/**
 * This class implements a hexadecimal converter where the value is printed out every time
 * {@link MyInteger} updates its value.
 *
 * Steps for updating this file:
 * 1. Register ourselves as an interested observer of "MyInteger"
 *
 * Modified from https://www.tutorialspoint.com/design_pattern/observer_pattern.htm
 *
 * @version 1.0
 */
public class HexaObserver implements IObserver {

    // Private data

    /**
     * MyInteger subject
     */
    private MyInteger integer;

    /**
     * No-argument constructor.
     *
     * @param mi MyInteger object, the subject this observer is interested in.
     *
     * @pre mi != null
     *
     * @post integer = mi AND mi.registerObserver(this)
     */
    public HexaObserver(MyInteger mi) 
    {
        integer = mi;
        integer.registerObserver(this);
    }

    /**
     * This method is called by the subject when it updates its value.
     *
     * @param value the value associated with the subject.
     *
     * @pre this observer must be registered to a subject
     *
     * @post prints the hexadecimal string representation of the value is printed to the consoleusing
     * Integer.toHexString AND integer = #integer
     */
    @Override
    public void update(int value) 
    {
        System.out.println("Hexadecimal: " + Integer.toHexString(value));
    }
}