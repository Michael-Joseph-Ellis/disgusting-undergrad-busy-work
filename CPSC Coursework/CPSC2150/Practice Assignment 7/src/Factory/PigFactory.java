package Factory;

import Models.AbsAnimal;
import Models.Pig;

public class PigFactory extends AbsAnimalFactory
{
    @Override
    public AbsAnimal make()
    {
        return new Pig();
    }
}
