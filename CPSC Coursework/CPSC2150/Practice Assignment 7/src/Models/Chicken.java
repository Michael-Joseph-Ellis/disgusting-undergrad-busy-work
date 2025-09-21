package Models;

public class Chicken extends AbsAnimal
{
    public Chicken()
    {
        makeSound();
    }

    @Override
    public void makeSound()
    {
        System.out.println("Cluck?");
    }
}
