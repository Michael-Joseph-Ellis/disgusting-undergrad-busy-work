package Models;

public class Pig extends AbsAnimal
{
    public Pig()
    {
        makeSound();
    }

    @Override
    public void makeSound()
    {
        System.out.println("Oink");
    }
}
