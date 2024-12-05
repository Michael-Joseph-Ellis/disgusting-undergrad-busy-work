public class Student
{
    private String name;
    private int age;
    private String email;

    /**
     * A parameterized constructor for students, accepts 3 params.
     * @param name the value to be set for name.
     * @param age the value to be set for age.
     * @param email the value to be set for email, but it contains '@'.
     * 
     * @pre [name must contain only letters] AND 0 < age < 100 AND [email must contain '@clemson.edu'
     * and contains only standard characters]
     * 
     * @post this.name = name AND this.age = age AND this.email = email 
     */

    public Student(String name, int age, String email)
    {
        this.name = name;
        this.age = age;
        this.email = email;
    }

    /**
     * Standard getter for name 
     * 
     * @return the name of the student
     * 
     * @pre this != null 
     *  
     * @post getName = [name with the first letter uppercased IFF the name is all lowercase
     * ELSE returns name as-is] AND name = #name (# means the current value of) AND age = #age AND email = #email
     * 
     */

    public String getName()
    {
        if(name.equals(name.toLowerCase()))
        {
            return Character.toUpperCase(name.charAt(0)) + name.substring(1);
        }
        return name;
    }

    /**
     * Standard getter for age 
     * 
     * @return the age of the student 
     * 
     * @pre this != null
     * 
     * @post getAge = age AND name = #name AND age = #age AND email = #email
     */
    public int getAge()
    {
        return age;
    }

    /**
     * Standard getter for email 
     * 
     * @return the email of the student 
     * 
     * @pre this != null
     * 
     * @post getEmail = email AND name = #name AND age = #age AND email = #email
     */

    public String getEmail()
    {
        return email;
    }

    /**
     * Standard setter for name 
     * 
     * @param aName the new name of the student 
     * 
     * @pre aName != null
     * 
     * @post name = aName AND age = #age AND email = #email
     */

    public void setName(String aName)
    {
        this.name = aName;
    }

    /**
     * Standard setter for age 
     * 
     * @param anAge the new age of the student 
     * 
     * @pre anAge > 0 AND anAge < 100
     * 
     * @post name = #name AND age = anAge AND email = #email
     */

    public void setAge(int anAge)
    {
        this.age = anAge;
    }

    /**
     * Standard setter for email 
     * 
     * @param anEmail the new email of the student 
     * 
     * @pre anEmail != null
     * 
     * @post name = #name AND age = #age AND email = anEmail
     */

    public void setEmail(String anEmail)
    {
        this.email = anEmail;
    }


    /**
     * Prints the values associated with students, one value per line. 
     * @param aStudent The student object with a name, age, and an email that we want to print the info of.
     * 
     * @pre aStudent != null
     * 
     * @post [prints aStudent's information, on each line, and doesn't change the data]
     * 
     * 
     */

    public static void printStudentInformation(Student aStudent)
    {
        System.out.println("Name: " + aStudent.getName());
        System.out.println("Age: " + aStudent.getAge());
        System.out.println("Email: " + aStudent.getEmail());
    }

    /**
     * Checks if two students are equal by comparing their name, age, and email. 
     * 
     * @param obj The object to compare to the current student object.
     * 
     * @pre obj != null AND obj instanceof Student for meaningful comparison
     *
     * @post equals = true IFF the name, age, and email of the two students are the same, else returns false
     * 
     * @return true if the name, age, and email of the two students are the same, else returns false
     */

    public boolean equals(Object obj)
    {
        if (obj == null)
            return false;
        if (obj == this)
            return true;
        if(obj instanceof Student other)
            return this.name.equals(other.name) && this.age == other.age && this.email.equals(other.email);
        else
            return false;
    }


}
