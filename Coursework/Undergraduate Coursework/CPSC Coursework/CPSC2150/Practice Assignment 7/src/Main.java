import Factory.AbsAnimalFactory;
import Factory.ChickenFactory;
import Factory.PigFactory;
import Models.AbsAnimal;
import Models.Chicken;
import Models.Pig;

public class Main
{
    public static void main(String[] args)
    {

        AbsAnimalFactory factory = new ChickenFactory();

        AbsAnimal animal1 = factory.make();
        AbsAnimal animal2 = factory.make();
        AbsAnimal animal3 = factory.make();
        AbsAnimal animal4 = factory.make();
        AbsAnimal animal5 = factory.make();
        AbsAnimal animal6 = factory.make();
        AbsAnimal animal7 = factory.make();

        factory = new PigFactory();

        AbsAnimal animal8 = factory.make();
        AbsAnimal animal9 = factory.make();
        AbsAnimal animal10 = factory.make();
        AbsAnimal animal11 = factory.make();
        AbsAnimal animal12 = factory.make();
        AbsAnimal animal13 = factory.make();
        AbsAnimal animal14 = factory.make();
        AbsAnimal animal15 = factory.make();

        /*AbsAnimal animal1 = new Chicken();
        AbsAnimal animal1 = new Pig();*/
    }
}