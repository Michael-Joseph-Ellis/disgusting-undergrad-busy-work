/**
 * IStack interface for stack operations push, pop, peek, isEmpty, isFull. Stacks
 * are used to store data in a Last In First Out (LIFO) order. The last element
 * added to the stack is the first element to be removed.
 *
 * @initialzation_ensures: stack is empty
 *
 * @defines: self: the stack
 *          top: the index of the top of the stack
 *          size: the max size of the stack
 *
 * @constraints: stack is empty if top is -1. The stack is full if top is equal to size - 1.
 *
 *
 */
public interface IStack {

    /**
     * Pushes an item onto the stack
     * @param item the item to be pushed onto the stack
     *
     * @pre stack is not full
     *
     * @post self = #self with item added to the top of the stack AND top = #top + 1
     *     AND size = #size
     */
    public void push(int item);


    /**
     * Removes and returns the top item from the stack
     * @return the top item from the stack
     *
     * @pre stack is not empty
     *
     * @post pop = The item at the top of the stack AND self = #self with the
     * top item removed AND top = #top - 1 AND size = #size
     */
    public int pop();

    public int getTop();

    /**
     * Returns the top item from the stack without removing it
     * @return the top item from the stack
     *
     * @pre stack is not empty
     *
     * @post peek = the item at the top of the stack AND self = #self
     * AND top = #top AND size = #size
     */
    default public int peek() 
    {
        System.out.println("IStack peek");
        int ret = pop();
        push(ret);
        return ret;
    }

    /**
     * Returns true if the stack is empty
     * @return true if the stack is empty, false otherwise
     *
     * @pre none
     *
     * @post isEmpty = true IFF [top = -1, False otherwise] AND
     * self = #self AND top = #top AND size = #size
     */
    default public boolean isEmpty()
    {
        return getTop() == -1;
    }

    /**
     * Returns true if the stack is full
     * @return true if the stack is full, false otherwise
     *
     * @pre none
     *
     * @post isFull = true IFF [top = the max size of the stack -1,
     * false otherwise] AND self = #self AND top = #top AND size = #size
     */
    public boolean isFull();
}
