package Factory;

import Models.Chicken;
import Models.AbsAnimal;

public class ChickenFactory extends AbsAnimalFactory
{
    @Override
    public AbsAnimal make()
    {
        return new Chicken();
    }
}
