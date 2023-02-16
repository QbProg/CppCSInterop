
namespace CSComponent
{
    public sealed class CSClass 
    {       
        public string Hello()
        {
            return "Hello from C#";
        }

        public string HelloRecallCpp()
        {
            CppComponent.Class c1 = new CppComponent.Class();
            return c1.Hello();
        }
    }
}