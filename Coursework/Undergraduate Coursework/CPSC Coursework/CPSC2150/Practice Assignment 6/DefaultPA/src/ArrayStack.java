public class ArrayStack implements IStack
{
    private int[] stack;
    private int top;
    private int size;

    public ArrayStack(int size)
    {
        this.size = size;
        stack = new int[size];
        top = -1;
    }

    default public void push(int item)
    {
        if (isFull())
        {
            System.out.println("Stack is full");
            return;
        }
        stack[++top] = item;
    }

    public int getTop()
    {
        return top;
    }

    public int pop()
    {
        if (isEmpty())
        {
            System.out.println("Stack is empty");
            return -1;
        }
        return stack[top--];
    }
}
