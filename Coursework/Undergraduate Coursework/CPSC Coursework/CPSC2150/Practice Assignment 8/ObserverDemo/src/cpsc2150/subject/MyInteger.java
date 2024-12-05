package cpsc2150.subject;

import java.util.ArrayList;
import java.util.List;

import cpsc2150.observer.IObserver;

/**
 * This class implements a mutable integer reference object, where it
 * notifies any interested observers about changes to its internal value.
 *
 * Steps for updating this file:
 * 1. Create and initialize a set/list of interested observers
 * 2. Notify our interested observers when we update our value
 * 3. Implement "registerObserver", "unregisterObserver" and "notifyObserver"
 *
 * Modified from https://www.tutorialspoint.com/design_pattern/observer_pattern.htm
 *
 * @version 1.0
 */
public class MyInteger {

    /**
     * List of interested observers
     */
	private List<IObserver> myObservers;

    /**
     * Integer value
     */
    private int myValue;


    /**
     * Default constructor for the MyInteger Object. Should set a default value
     * of 0 and initialize the list of observers.
     *
     * @pre none
     *
     * @post myValue = 0 AND myObservers = new ArrayList<IObserver>()
     */
    public MyInteger() 
    {
        myValue = 0;
        myObservers = new ArrayList<>();
    }

    /**
     * standard getter for the integer value
     *
     * @return The internal integer value.
     *
     * @pre none
     *
     * @post getValue = myValue AND myValue = #myValue AND myObservers = #myObservers
     */
    public int getValue() 
    {
        return myValue;
    }

    /**
     * This method updates the wrapped integer value.
     *
     * @param newVal A new integer value
     *
     * @pre none
     *
     * @post myValue = newVal AND invokes notifyAllObservers()
     */
    public void updateValue(int newVal) 
    {
        myValue = newVal;
        this.notifyAllObservers();
    }

    /**
     * Register argument as observer/listener of this
     *
     * @param obs An interested observer
     *
     * @pre obs != null
     *
     * @post myObservers = #myObservers U {obs} AND myValue = #myValue
     */
    public void registerObserver(IObserver obs) 
    {
        myObservers.add(obs);
    }

    /**
     * Register argument as observer/listener of this
     *
     * @param obs An uninterested observer
     *
     * @pre obs != null AND obs in myObservers
     *
     * @post myObservers = #myObservers - {obs} AND myValue = #myValue
     */
    public void unregisterObserver(IObserver obs) 
    {
        myObservers.remove(obs);
    }

    /**
     * Notifies all interested observers that we have changed our internal value.
     *
     * @pre |myObservers| > 0
     *
     * @post myObservers = #myObservers AND myValue = #myValue
     */
    public void notifyAllObservers() 
    {
        for(IObserver obs : myObservers) 
        {
            obs.update(this.getValue());
        }
    }

}