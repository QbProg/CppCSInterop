using CppComponent;

namespace CSTextEXE
{
    internal class MainClass
    {

        static void Main(string[] args)
        {
            CppComponent.Class c = new CppComponent.Class();
            string s = c.Hello();
            System.Console.WriteLine(s);
        }
    }
}