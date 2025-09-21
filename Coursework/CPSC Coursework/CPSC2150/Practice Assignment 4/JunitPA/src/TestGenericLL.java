import org.junit.*;
import static org.junit.Assert.*;

public class TestGenericLL 
{

    //Scope: constructor, toString
    @Test 
    public void test_Constructor_empty() 
    {
        genericLL<Integer> obsLL = new genericLL<>();
        assertNull(obsLL.toString());
        //assertTrue(false);
    }

    //Scope: insert
    @Test 
    public void test_Constructor_length3() 
    {
        genericLL<Integer> obsLL = new genericLL<>();
        obsLL.insert(1);
        obsLL.insert(3);
        obsLL.insert(2);
        String obsStr = obsLL.toString();
        String expStr = "1 3 2 ";
        assertTrue(obsStr.equals(expStr));
    }`

}
