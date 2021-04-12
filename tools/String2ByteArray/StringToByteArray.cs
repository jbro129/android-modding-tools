using System;
using System.Text;

class Program
{
    static void Main()
    {
        Console.Write("Please enter your string: ");

        string cstr = Console.ReadLine();

        // Invoke GetBytes method.
        // ... You can store this array as a field!
        byte[] array = Encoding.ASCII.GetBytes(cstr);

        // Loop through contents of the array.
        foreach (byte element in array)
        {
            Console.WriteLine("{0} = {1}", element, (char)element);
        }
    }
}