package cpsc2150.observer;

/**
 * This interface specifies the callback method that all numeric converters
 * must implement in order to print out the converted value.
 *
 * --No change is required in this file.--
 *
 * Modified from https://www.tutorialspoint.com/design_pattern/observer_pattern.htm
 *
 * @version 1.0
 */
public interface IObserver {

    /**
     * This method serves as the callback method in this example,
     * where we will use the value provided and print out the appropriate
     * converted value.
     *
     * @param value Value provided.
     */
    public void update(int value);

}