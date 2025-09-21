import java.util.ArrayList;

public class ListStack implements IStack
{
    private ArrayList<Integer> stack;
    private int top;
    private int size;

    public ListStack(int size)
    {
        this.size = size;
        stack = new ArrayList<Integer>(size);
        top = -1;
    }

    public void push(int item)
    {
        if (isFull())
        {
            System.out.println("Stack is full");
            return;
        }
        stack.add(++top, item);
    }

    public int getTop()
    {
        return top;
    }

    @Override
    public int peek() 
    {
        System.out.println("ListStack peek");
        return stack.get(top);
    }

    public int pop()
    {
        if (isEmpty())
        {
            System.out.println("Stack is empty");
            return -1;
        }
        return stack.remove(top--);
    }

    public boolean isEmpty()
    {
        return top == -1; 
    }
}
