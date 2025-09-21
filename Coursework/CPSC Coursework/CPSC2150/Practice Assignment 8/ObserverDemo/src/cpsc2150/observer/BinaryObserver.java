package cpsc2150.observer;

import cpsc2150.subject.MyInteger;

/**
 * This class implements a binary converter where the value is printed out every time
 * {@link MyInteger} updates its value.
 *
 * Steps for updating this file:
 * 1. Register ourselves as an interested observer of "MyInteger"
 *
 * Modified from https://www.tutorialspoint.com/design_pattern/observer_pattern.htm
 *
 * @version 1.0
 */
public class BinaryObserver implements IObserver {


    /**
     * MyInteger subject
     */
    private MyInteger integer;

    // Constructor

    /**
     * No-argument constructor.
     *
     * @param mi MyInteger object, the subject this observer is interested in.
     *
     * @pre mi != null
     *
     * @post integer = mi AND mi.registerObserver(this)
     */
    public BinaryObserver(MyInteger mi) 
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
     * @post prints the binary string representation of the value is printed to the console using
     * Integer.toBinaryString AND integer = #integer
     */
    @Override
    public void update(int value) 
    {
        System.out.println("Binary: " + Integer.toBinaryString(value));
    }
}