package cpsc2150;

import cpsc2150.observer.BinaryObserver;
import cpsc2150.observer.HexaObserver;
import cpsc2150.observer.IObserver;
import cpsc2150.observer.OctalObserver;
import cpsc2150.subject.MyInteger;

/**
 * This is the main driver class for our example.
 *
 * --No change is required in this file.--
 *
 * Modified from https://www.tutorialspoint.com/design_pattern/observer_pattern.htm
 *
 * @version 1.0
 */
public class ObserverDemo {

    /**
     * This is the main entry point to our program.
     *
     * @param args Command line arguments (Not used)
     */
    public static void main(String[] args) {
        MyInteger integer = new MyInteger();
        IObserver hex = new HexaObserver(integer);
        IObserver octal = new OctalObserver(integer);
        IObserver binary = new BinaryObserver(integer);

        System.out.println("First value change: 15");
        integer.updateValue(15);
        
        integer.unregisterObserver(octal);

        System.out.println("-----------------------");
        System.out.println("Second value change: 10");
        integer.updateValue(10);

        integer.unregisterObserver(hex);
        integer.registerObserver(octal);

        System.out.println("-----------------------");
        System.out.println("Third value change: 999");
        integer.updateValue(999);
    }
}